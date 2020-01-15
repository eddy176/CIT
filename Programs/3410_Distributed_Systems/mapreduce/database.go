package mapreduce

import (
	"database/sql"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
)

func openDatabase(path string) (*sql.DB, error) {
	db, err := sql.Open("sqlite3", path)
	Fail("opening database open", err)
	_, err = db.Exec(`pragma synchronous = off;`)
	Fail("opening database synchronous", err)
	_, err = db.Exec(`pragma journal_mode = off;`)
	Fail("opening database journal mode", err)
	return db, nil
}

func createDatabase(path string) (*sql.DB, error) {
	os.Remove(path)
	db, err := sql.Open("sqlite3", path)
	if err != nil {
		log.Printf("Failed to create database with path %s\n", path)
		return nil, err
	}
	_, err = db.Exec(`pragma synchronous = off;`)
	if err != nil {
		return nil, err
	}
	_, err = db.Exec(`pragma journal_mode = off;`)

	_, err = db.Exec(`create table pairs (key text, value text);`)

	return db, nil
}

func rowCount(db *sql.DB) (int, error) {
	rows, err := db.Query("select count(1) from pairs;")
	if err != nil {
		return -1, err
	}
	defer rows.Close()
	count := 0
	for rows.Next() {
		err := rows.Scan(&count)
		if err != nil {
			return -1, err
		}
	}
	return count, nil
}

func splitDatabase(source, outputPattern string, m int) ([]string, error) {
	db, err := openDatabase(source)
	Fail("split database", err)
	defer db.Close()

	count, err := rowCount(db)
	Fail("split database querying pairs", err)
	fmt.Println("Count: ", count)
	if count < m {
		log.Fatal("count < m error")
	}
	// make a list of databases
	outputdatabases := make([]*sql.DB, 0)
	// make a list of names
	names := make([]string, 0)
	// loop up to m
	for i := 0; i < m; i++ {
		// get the output name
		namestring := fmt.Sprintf(outputPattern, i)
		// create new database
		outputdb, err := createDatabase(namestring)
		Fail("split database", err)
		defer outputdb.Close()
		// append new database to list
		outputdatabases = append(outputdatabases, outputdb)
		// append new name to list
		names = append(names, namestring)
	}
	// get pairs from db
	rows, err := db.Query("select key, value from pairs;")
	Fail("split databases selecting", err)
	defer rows.Close()
	index := 0
	// for each pair
	for rows.Next() {
		// get pair from rows
		pair, err := getPair(rows)
		Fail("split database", err)
		// insert pair into output databases at the index mod the number of workers
		err = insertPair(pair, outputdatabases[index%m])
		Fail("split databases insert", err)
		index++
	}
	return names, nil
}

func mergeDatabases(urls []string, path string, temp string) (*sql.DB, error) {
	outputdb, err := createDatabase(path)
	Fail("merge db createdb", err)
	for _, url := range urls {
		err = download(url, temp)
		Fail("merge db createdb download", err)
		err = gatherInto(outputdb, temp)
		Fail("merge db createdb gatherinto", err)
		err = os.Remove(temp)
		Fail("merge db createdb remove", err)
	}
	return outputdb, nil
}

func gatherInto(db *sql.DB, path string) error {
	query := fmt.Sprintf("attach '%s' as merge;", path) // ?
	_, err := db.Exec(query)
	if err != nil {
		log.Printf("Error executing query: attach %s as merge.\n", path)
		return err
	}
	
	_, err = db.Exec(`insert into pairs select * from merge.pairs;`)
	Fail("Gatherinto insert", err)

	_, err = db.Exec(`detach merge;`)
	Fail("Gatherinto merge detach", err)

	return nil
}

func download(url, path string) error {
	mpath, err := os.Create(path)
	Fail("Download os create", err)
	defer mpath.Close()

	// get body from url
	res, err := http.Get(url)
	Fail("Download get", err)
	defer res.Body.Close()

	// read body into mpath
	_, err = io.Copy(mpath, res.Body)
	Fail("Download opendb", err)

	return nil
}

func insertPair(pair Pair, db *sql.DB) error {
	_, err := db.Exec(
		"INSERT INTO pairs (key, value) VALUES (?, ?);",
		pair.Key,
		pair.Value)
	Fail("insertpair", err)
	return nil
}
