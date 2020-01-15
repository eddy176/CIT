package main

import (
	"fmt"
	"os"
)

const (
	defaultHost = "localhost"
	defaultPort = "3410"
	MAX_STEPS   = 3
)

func main() {
	localNode := new(Node)
	localNode.Kill = make(chan struct{})
	localNode.Bucket = make(map[string]string)
	localNode.Ip = getLocalAddress()
	localNode.Port = ":" + defaultPort
	localNode.Address = localNode.Ip + localNode.Port
	fmt.Printf("LocalNode Address: %v", localNode.Address)

	go func() {
		<-localNode.Kill // block and wait for kill
		os.Exit(0)       // close and exit
	}()
	shell(localNode)
}
