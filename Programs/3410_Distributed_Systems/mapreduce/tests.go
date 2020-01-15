package mapreduce

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"path/filepath"
)

//Address is my local machine address
// var Address = ""

func main() {
	M := 9
	R := 3
	tempdir := filepath.Join("./tmp/", fmt.Sprintf("mapreduc.%d", os.Getpid()))
	log.Printf("Tmp dir is %s\n", tempdir)
	address := "http://localhost"

	dbPath := filepath.Join(tempdir, mapSourceFile(0))
	os.MkdirAll(dbPath, os.FileMode(0777))
	db, err := createDatabase(dbPath)
	Fail("Tests createdb", err)
	defer db.Close()

	go func() {
		http.Handle("/data/", http.StripPrefix("/data/", http.FileServer(http.Dir("mnt/c/golang/src/github.com/kacystocks/mapreduce"))))
		err := http.ListenAndServe(":8080", nil)
		Fail("Test listenandserve", err)
	}()

	for i := 0; i < 70; i++ {
		err = insertPair(Pair{fmt.Sprintf("%d", i), fmt.Sprintf("%d", i%7)}, db)
		Fail("Tests insertpair", err)
	}
	db.Close()

	c := Client{}
	mapper := MapTask{M, R, 0, address}
	mapper.Process(tempdir, c)

	reducer := ReduceTask{M, R, 1, []string{address}}
	reducer.Process(tempdir, c)
}
