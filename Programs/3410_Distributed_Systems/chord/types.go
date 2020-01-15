package main

import (
	"sync"
)

// Command is a struct that has a verb and a function

// Finger is an address of a node

// Node is a struct that has a finger table, successors, and predecessor
type Node struct {
	Ip          string
	Next        int
	Finger      []string
	Successor   string
	Successors  []string
	Predecessor string
	Ring        bool
	Bucket      map[string]string
	Lock        sync.Mutex
	Address     string
	Port        string
	Kill    chan struct{}
}

// Nothing is an empty struct
type Nothing struct{}

// Pair is a struct with keys and values in it
type Pair struct {
	Key   string
	Value string
}

// FoundNode is a struct
type FoundNode struct {
	Found bool
	Node  string
}

// KeyFound is a struct
type KeyFound struct {
	Found   bool
	Address string
}
