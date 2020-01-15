package mapreduce

import "sync"

// Client is an empty struct
type Client struct{}

// Nothing is an empty struct used for stuffs...
type Nothing struct{}

// Interface holds a Map interface(key:value, pair output channel)
// and it holds a Reduce interface(key:values channel, pair output channel)
type Interface interface {
	Map(key, value string, output chan<- Pair) error
	Reduce(key string, values <-chan string, output chan<- Pair) error
}

// Pair is a key-value struct
type Pair struct {
	Key   string
	Value string
}

// MapTask holds total map and reduce task #s, current #, and its address
type MapTask struct {
	M, R       int    // total number of map and reduce tasks
	N          int    // map task number, 0-based
	SourceHost string // address of host with map input file
}

// ReduceTask holds total map and reduce task #s, current #, addresses of map workers
type ReduceTask struct {
	M, R        int      // total number of map and reduce tasks
	N           int      // reduce task number, 0-based
	SourceHosts []string // addresses of map workers
}

// Worker is a struct for worker nodes
type Worker struct {
	Address   string
	Available bool
	Kill      chan bool
	Dir       string
	Client    Interface
}

// Master is a struct for the master node
type Master struct {
	M, R            int
	Mut             sync.Mutex
	Kill            chan bool
	Files           string
	Address         string
	Workers         []*Worker
	MapTasks        []MapTask
	ReduceTasks     []*ReduceTask
	MapCompleted    int
	ReduceCompleted int
	OutputURLs      []string
}
