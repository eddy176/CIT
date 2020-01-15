package main

import "sync"

// Nothing is an empty struct
type Nothing struct{}

// Node is a node
type Node struct {
	IP             string
	Port           string
	Address        string
	Replicas       []string
	Terminate      chan struct{}
	Bucket         map[string]string
	History        []string
	HighestSlot    int
	HighestPrepare int
	HighestAccept  Accept
	lock           sync.Mutex
	Cell           bool
	Generator      int
}

// Pair is a Key-Value pair
type Pair struct {
	Key   string
	Value string
}

// Accept is used when accepted
type Accept struct {
	Okay     bool
	Slot     int
	Sequence int
	Command  string
	Tag      string
}
