package main

import (
	"fmt"
)

// Ping is a node method
func (n *Node) Ping(node Node, response *Nothing) error {
	fmt.Println("Received Ping")
	return nil
}