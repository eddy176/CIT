package main

import (
	"fmt"
	"log"
	"net"
	"net/http"
	"net/rpc"
	"time"
)

func server(node *Node) {
	// grab the address of the current node
	address := node.Port
	// register the node
	rpc.Register(node)
	rpc.HandleHTTP()
	listener, err := net.Listen("tcp", address)
	if err != nil {
		log.Fatal("listen error:", err)
	}
	fmt.Printf("Listening on %v\n", address)

	go func() {
		if err := http.Serve(listener, nil); err != nil { // serve
			log.Fatalf("http.Serve: %v", err)
		}
	}()
	fmt.Println("Server up")
}

// call is a helper for server and client
func call(address string, method string, args interface{}, response interface{}) error {
	// client calls an RPC connection to the address specified
	client, err := rpc.DialHTTP("tcp", address)
	if err != nil {
		log.Printf("rpc.DialHTTP: %v", err)
		return err
	}
	// prepares to close it
	defer client.Close()

	// performs RPC calls, using reflection- we can figure out what needs done
	if err = client.Call(method, args, response); err != nil {
		log.Printf("client.Call %s: %v", method, err)
		return err
	}
	return nil
}

func join(localNode *Node, address string) error {
	var junk Nothing
	if err := call(address, "Node.Ping", junk, &junk); err != nil {
		log.Printf("couldn't establish connection: %v\n", err)
		return err
	}
	localNode.Successor = address
	localNode.Predecessor = ""
	if err := call(localNode.Address, "Node.Notify", localNode.Address, &junk); err != nil {
		log.Printf("couldn't update: %v", err)
	}

	go func() {
		// forever loop with a sleep timer
		// stabilize every 5 seconds
		for {
			localNode.Stabilize(junk, &junk)
			time.Sleep(5 * time.Second)
		}
	}()
	return nil
}
