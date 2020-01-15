package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

func shell(localNode *Node) {
	log.Printf("\nStarting interactive shell\n")
	log.Println("commands: help, quit, port, create, join, dump, put, get, delete, putrandom")

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		line = strings.TrimSpace(line)

		parts := strings.SplitN(line, " ", 3)
		if len(parts) > 1 {
			parts[1] = strings.TrimSpace(parts[1])
		}
		if len(parts) == 0 {
			continue
		}
		var junk Nothing
		switch parts[0] {

		case "help":
			fmt.Println("commands: help, quit, port, create, join, dump, put, get, delete, putrandom")
			continue

		case "create":
			var err error
			if localNode.Ring == false {
				server(localNode)
				if err = join(localNode, localNode.Address); err == nil {
					localNode.Ring = true
					log.Printf("\nLocal address: %v\n", localNode.Address)
				}
			} else {
				log.Printf("Ring already exists: %v\n", err)
			}

		case "put":
			if len(parts) != 3 {
				log.Printf("Usage: put <key> <value>")
				continue
			}
			pair := Pair{parts[1], parts[2]}

			if err := call(localNode.Address, "Node.Post", pair, &junk); err != nil {
				log.Printf("calling Node.Post: %v", err)
			} else {
				log.Printf("Inserted: { %v:%v }", pair.Key, pair.Value)
			}

		case "putrandom":
			pair := Pair{"thisisarandomkey", "thisisarandomvalue"}

			if err := call(localNode.Address, "Node.Post", pair, &junk); err != nil {
				log.Printf("calling Node.Post: %v", err)
			} else {
				log.Printf("Inserted: %v:%v", pair.Key, pair.Value)
			}

		case "port":
			if len(parts) == 1 {
				log.Printf("Current port: %v", localNode.Port)
			} else if len(parts) == 2 {
				if !localNode.Ring {
					localNode.Port = ":" + parts[1]
					localNode.Address = defaultHost + ":" + parts[1]
					fmt.Printf("Port changed to: %v\n", localNode.Address)
				} else {
					log.Printf("Error in port: already part of the ring.")
				}
			} else {
				log.Println("Usage: port <number>")
			}

		case "ping":
			if len(parts) == 1 {
				if err := call(localNode.Address, "Node.Ping", localNode, &junk); err != nil {
					log.Printf("Server unreachable: %v", err)
				} else {
					fmt.Println("Server responded")
				}
			} else if len(parts) == 2 {
				if err := call(localNode.Ip+":"+parts[1], "Node.Ping", localNode, &junk); err != nil {
					log.Printf("Server unreachable: %v", err)
				} else {
					fmt.Println("Server responded")
				}
			}

		case "join":
			if len(parts) < 2 || len(parts) > 2 {
				log.Printf("Usage: join <address>")
				continue
			}
			if localNode.Ring == false {
				server(localNode)
				if err := join(localNode, ":"+parts[1]); err == nil {
					localNode.Ring = true
				} else {
					log.Printf("Invalid address: %v\n", err)
				}
			} else {
				log.Println("Ring already exists.")
			}

		case "get":
			if len(parts) != 2 {
				log.Printf("Usage: get <key>")
				continue
			}
			var message string
			oldmessage := message
			if err := call(localNode.Address, "Node.Get", parts[1], &message); err != nil {
				log.Printf("calling Node.Get %v", err)
			}
			if message == oldmessage {
				fmt.Println("Key not found")
			} else {
				fmt.Println("Value: " + message)
			}

		case "delete":
			if len(parts) != 2 {
				log.Printf("Usage: delete <key>")
				continue
			}
			var message string
			if err := call(localNode.Address, "Node.Delete", parts[1], &message); err != nil {
				log.Printf("calling Node.Delete %v", err)
			} else {
				log.Println("Deleted")
			}

		case "quit":
			if localNode.Successor == localNode.Address {
				log.Printf("Shutting down ring: %v", localNode.Address)
				localNode.Kill <- junk
			} else {
				log.Printf("killing current node: %v", localNode.Address)
				localNode.Kill <- junk
			}

		case "dump":
			fmt.Printf("=================\nNode info:\nlocal node: %v\nsuccessor: %v\npredecessor: %v\nbucket: \n", localNode.Address, localNode.Successor, localNode.Predecessor)
			for index := range localNode.Bucket {
				fmt.Printf("\t{ %v : %v }\n===================\n", index, localNode.Bucket[index])
			}

		case "dumpkey":
			if len(parts) != 2 {
				log.Printf("you must specify a port")
				continue
			}
			for index := range localNode.Bucket {
				fmt.Printf("\t%v\n===================\n", index)
			}

		case "dumpaddr":
			if len(parts) != 2 {
				log.Printf("you must specify a port")
				continue
			}
			for index := range localNode.Finger {
				fmt.Printf("\t{ %v : %v }\n===================\n", index, localNode.Finger[index])
			}
			// use dht lookup to find by address
			// fmt.Printf("Node info\nid: %v\nfinger: %v\nsuccessor: %v\npredecessor: %v\n", Nodes[address].id, Nodes[address].Finger, Nodes[address].Successor, Nodes[address].Predecessor)

		case "dumpall":
			fmt.Printf("=================\nNode info:\nlocal node: %v\nsuccessor: %v\npredecessor: %v\nbucket: \n", localNode.Address, localNode.Successor, localNode.Predecessor)
			for index := range localNode.Bucket {
				fmt.Printf("\t{ %v : %v }\n===================\n", index, localNode.Bucket[index])
			}
			for index := range localNode.Finger {
				fmt.Printf("\t{ %v : %v }\n===================\n", index, localNode.Finger[index])
			}

		default:
			log.Printf("I don't recognize your command")
		}
	}
	if err := scanner.Err(); err != nil {
		log.Printf("scanner error: %v", err)
	}
}
