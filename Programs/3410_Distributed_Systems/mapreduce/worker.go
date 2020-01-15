package mapreduce

import (
	"database/sql"
	"hash/fnv"
	"log"
	"path/filepath"
)

// Process is a MapTask method that takes a temp directory and client interface
// it processes a single Map task
func (task *MapTask) Process(tempdir string, client Interface) error {
	// join
	outputpath := filepath.Join(tempdir, mapInputFile(task.N))
	// download input file
	err := download(task.SourceHost, outputpath)
	Fail("map process download", err)
	// make list of databases
	reduceDB := make([]*sql.DB, 0)
	// loop up to R
	for i := 0; i < task.R; i++ {
		// get output of joined filename
		output := filepath.Join(tempdir, mapOutputFile(task.N, i))
		// create databases
		db, err := createDatabase(output)
		Fail("map process create outputdb", err)
		// don't forget to close all of them
		defer db.Close()
		// append db to reducedb list
		reduceDB = append(reduceDB, db)
	}

	input, err := openDatabase(outputpath)
	Fail("map process open inputdb", err)
	defer input.Close()
	rows, err := input.Query("select key, value from pairs;")
	Fail("map process input query", err)
	defer rows.Close()
	// run function?? Russ gave us this
	outputfunc := func(output chan Pair, ack chan bool) {
		for pair := range output {
			hash := fnv.New32() // from the stdlib package hash/fnv
			hash.Write([]byte(pair.Key))
			r := int(hash.Sum32()) % task.R
			insertPair(pair, reduceDB[r])
		}
		ack <- true
	}

	// db query to select all pairs from source file
	for rows.Next() {
		pairchan := make(chan Pair, 100)
		ackchan := make(chan bool, 1)
		// get keys and values
		pair, err := getPair(rows)
		Fail("map process rows getpair", err)
		// call map on pair
		// replace key and value with pair.key and pair.value?
		go client.Map(pair.Key, pair.Value, pairchan)
		Fail("map process rows", err)
		go outputfunc(pairchan, ackchan)
		<-ackchan
	}
	// Gather all pair objects client feeds through output channel and insert
	// each pair into appropriate output database. process stops when client
	// closes the channel
	return nil
}

// Process is a ReduceTask method that takes a tempdir, client interface
func (task *ReduceTask) Process(tempdir string, client Interface) error {
	// merge all appropriate output dbs from map phase
	input := filepath.Join(tempdir, reduceInputFile(task.N))
	log.Printf("This is input %v\n", input)
	// create input db
	tempFile := reduceTempFile(task.N)
	// merge the input and temp
	source, err := mergeDatabases(task.SourceHosts, input, tempFile)
	Fail("reduce process merge", err)
	defer source.Close()
	log.Println("Databases merged")
	// reduce
	outputFile := reduceOutputFile(task.N)
	// get the output path
	outputPath := filepath.Join(tempdir, outputFile)

	// create output database
	outputdb, err := createDatabase(outputPath)
	Fail("reduce process create outputdb", err)
	defer outputdb.Close()

	// process all pairs in correct order
	rows, err := source.Query(`select key, value from pairs order by key, value;`)
	Fail("reduce process query", err)
	defer rows.Close()

	// set an empty string to test current vs past
	tempkey := ""
	// create client channel
	inchan := make(chan string, 100)
	// create server channel
	outchan := make(chan Pair, 100)
	// create boolean channel
	boolchan := make(chan bool)

	// make handlePairs
	handlePairs := func(values chan Pair) {
		// for every pair, insert it into the db
		for pair := range values {
			insertPair(pair, outputdb)
		}
		// return true to the channel
		boolchan <- true
	}

	// for each row:
	for rows.Next() {
		// get the pair
		pair, err := getPair(rows)
		Fail("reduce process pair rows", err)
		// if this key != last key, bool = true
		if tempkey == "" {
			// save current key
			tempkey = pair.Key
			// go reduce!!
			go client.Reduce(tempkey, inchan, outchan)
			// go handle pairs!!
			go handlePairs(outchan)
		}
		// when encounter a new key unless first key:
		if tempkey != pair.Key {
			// close out previous call to client.reduce
			// close input channel->so reduce knows it's done for the given key
			close(inchan)
			<-boolchan
			// start new call to client.reduce
			inchan = make(chan string, 100)
			outchan = make(chan Pair, 100)
			tempkey = pair.Key
			go client.Reduce(tempkey, inchan, outchan)
			go handlePairs(outchan)
		}
		inchan <- pair.Value
	}
	// close the channel
	close(inchan)
	// wait to finish
	<-boolchan
	return nil
}
