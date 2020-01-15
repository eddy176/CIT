package main

import (
	"fmt"
	"log"
	"net"
	"net/http"
	"net/rpc"
)

func server(node *Node) {
	address := node.Port
	rpc.Register(node)
	rpc.HandleHTTP()
	listener, err := net.Listen("tcp", address)
	fmt.Println("Listening...")
	if err != nil {
		log.Fatal("listen error:", err)
	}
	log.Printf("Listening on %v", address)

	go func() {
		if err := http.Serve(listener, nil); err != nil {
			log.Fatalf("http.Serve: %v", err)
		}
	}()
}

func call(address string, method string, args interface{}, response interface{}) error {
	client, err := rpc.DialHTTP("tcp", address)
	if err != nil {
		log.Printf("rpc.DialHTTP: %v", err)
		return err
	}
	defer client.Close()

	if err = client.Call(method, args, response); err != nil {
		log.Printf("client.Call %s: %v", method, err)
		return err
	}
	return nil
}
