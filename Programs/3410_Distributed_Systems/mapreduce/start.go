package mapreduce

import (
	"flag"
	"fmt"
	"log"
	"net"
	"net/http"
	"net/rpc"
	"os"
	"path/filepath"
	"runtime"
)

func Start(client Interface) error {
	runtime.GOMAXPROCS(1)
	var master, split bool
	var m, r int
	var ip, port, dir string
	// get tempdir
	tempdir := filepath.Join("./tmp/", fmt.Sprintf("reduce.%d", os.Getpid()))
	// set flags
	flag.BoolVar(&master, "master", false, "Set instance to master")
	flag.BoolVar(&split, "split", false, "Only split the database")
	flag.IntVar(&m, "m", 9, "Number of mappers")
	flag.IntVar(&r, "r", 3, "Number of reducers")
	flag.StringVar(&ip, "ip", "", "IP Adress of master")
	flag.StringVar(&port, "port", "3410", "Port of master")
	flag.StringVar(&dir, "dir", tempdir, "Directory for storage used by client or master")
	flag.Parse()
	// make the directory with full access
	err := os.MkdirAll(dir, os.FileMode(0777))
	Fail("Start: MkdirAll", err)

	// Only split database
	if split {
		log.Println("Splitting database and quit")
		log.Println(os.Args[len(os.Args)-1])
		outPath := filepath.Join(dir, "output-%d.sqlite3")
		path := os.Args[len(os.Args)-1]
		result, err := splitDatabase(path, outPath, m)
		Fail("Start: splitDatabase", err)
		log.Fatalf("Database %s was split into %v\n", path, result)
	}

	localIP := getLocalAddress()
	address := net.JoinHostPort(localIP, port)
	log.Printf("Address is %s\n", address)
	// Start master
	if master {
		mTasks := make([]MapTask, 0)
		for i := 0; i < m; i++ {
			source := makeURL(address, fmt.Sprintf("output-%d.sqlite3", i))
			mTasks = append(mTasks, MapTask{M: m, R: r, N: i, SourceHost: source})
		}
		rTasks := make([]*ReduceTask, 0)
		for i := 0; i < r; i++ {
			rTasks = append(rTasks, &ReduceTask{M: m, R: r, N: i, SourceHosts: make([]string, 0)})
		}
		masterState := Master{
			M:               m,
			R:               r,
			Kill:            make(chan bool),
			Files:           dir,
			Address:         address,
			Workers:         make([]*Worker, 0),
			MapTasks:        mTasks,
			ReduceTasks:     rTasks,
			MapCompleted:    0,
			ReduceCompleted: 0,
			OutputURLs:      make([]string, 0)}

		log.Println("This node is the master")
		// log.Printf("%+v\n", masterState)
		masterState.startListening()
		<-masterState.Kill
		log.Println("Received kill")
	} else {
		// Start worker
		if ip == "" {
			log.Fatalln("Worker needs to know address of master")
		}
		workerState := Worker{
			Address: address,
			Kill:    make(chan bool),
			Dir:     dir,
			Client:  client}
		log.Printf("This node is a worker.\nTemp dir is %s\n", dir)
		// log.Printf("%+v\n", workerState)
		workerState.startListening()
		err := call(ip, "Master.Register", address, &struct{}{})
		Fail("Register with master", err)

		// log.Printf("THIS IS THE WORKERSTATE: %v\n", workerState.Kill)

		<-workerState.Kill

		log.Println("Received kill")
	}
	err = os.RemoveAll(tempdir)
	Fail("Start: Remove tempdir", err)
	return nil
}

func getLocalAddress() string {
	var localaddress string

	ifaces, err := net.Interfaces()
	if err != nil {
		panic("getLocalAddress: failed to find network interfaces")
	}

	// find the first non-loopback interface with an IPv4 address
	for _, elt := range ifaces {
		if elt.Flags&net.FlagLoopback == 0 && elt.Flags&net.FlagUp != 0 {
			addrs, err := elt.Addrs()
			if err != nil {
				panic("getLocalAddress: failed to get addresses for network interface")
			}

			for _, addr := range addrs {
				if ipnet, ok := addr.(*net.IPNet); ok {
					if ip4 := ipnet.IP.To4(); len(ip4) == net.IPv4len {
						localaddress = ip4.String()
						break
					}
				}
			}
		}
	}
	if localaddress == "" {
		panic("localaddress: failed to find non-loopback interface with valid IPv4 address")
	}

	return localaddress
}

func (master *Master) startMaster(address string, dir string) {
	go func() {
		http.Handle("/data/", http.StripPrefix("/data", http.FileServer(http.Dir(dir))))
		err := http.ListenAndServe(address, nil)
		Fail("tests: http.ListenAndServe", err)
	}()
}

func call(address string, method string, request interface{}, reply interface{}) error {
	client, err := rpc.DialHTTP("tcp", address)
	if err != nil {
		return err
	}
	defer client.Close()
	err = client.Call(method, request, reply)
	return err
}

func (m *Master) startListening() {
	go func() {
		rpc.Register(m)
		rpc.HandleHTTP()
		http.Handle("/data/", http.StripPrefix("/data", http.FileServer(http.Dir(m.Files))))

		l, e := net.Listen("tcp", m.Address)
		if e != nil {
			log.Fatal("listen error:", e)
		} else {
			log.Printf("Now listening on %v, serving from %s\n", m.Address, m.Files)
		}

		err := http.Serve(l, nil)
		Fail("Master: startListening", err)
	}()
}

func (w *Worker) startListening() {
	go func() {
		rpc.Register(w)
		rpc.HandleHTTP()
		http.Handle("/data/", http.StripPrefix("/data", http.FileServer(http.Dir(w.Dir))))

		l, e := net.Listen("tcp", w.Address)
		if e != nil {
			log.Fatal("listen error:", e)
		} else {
			log.Printf("Now listening on %v\n, serving from %s\n", w.Address, w.Dir)
		}

		err := http.Serve(l, nil)
		Fail("Worker: startListening", err)
	}()
}
