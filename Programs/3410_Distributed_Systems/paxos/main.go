package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"
)

const (
	defaultAddress = "localhost"
	defaultPort    = "3410"
)

func main() {
	node := new(Node)
	node.Bucket = make(map[string]string)
	node.Terminate = make(chan struct{})
	node.HighestSlot = 0
	node.HighestPrepare = -1
	node.HighestAccept.Slot = -1

	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	node.Generator = r.Intn(40)

	args := os.Args
	args = os.Args[1:]
	node.IP = getLocalAddress()
	node.Port = ":" + args[0]
	node.Address = string(node.IP) + string(node.Port)
	fmt.Println("My address: " + node.Address)

	fmt.Println(args)
	for _, value := range args {
		node.Replicas = append(node.Replicas, node.IP + ":" + value)
	}

	server(node)
	go func() {
		<-node.Terminate
		os.Exit(0)
	}()
	shell(node)
}
