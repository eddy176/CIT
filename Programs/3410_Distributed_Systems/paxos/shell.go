package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

func shell(node *Node) {
	var rubbish Nothing
	fmt.Println("NODE ONLINE")
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		line = strings.TrimSpace(line)

		commands := strings.SplitN(line, " ", 3)
		if len(commands) > 1 {
			commands[1] = strings.TrimSpace(commands[1])
		}
		if len(commands) == 0 {
			continue
		}

		switch commands[0] {
			case "quit":
				if len(node.Replicas) == 1 {
					fmt.Println("Dissolving cell")
				}
				node.Terminate <- struct{}{}
			case "help":
				printCommands()
			case "ping":
				if len(commands) == 1 {
					if err := call(node.Address, "Node.Ping", node, &rubbish); err != nil {
						log.Printf("Server unreachable: %v", err)
					} else {
						fmt.Println("Server responded")
					}
				} else if len(commands) == 2 {
					if err := call(node.IP + ":"+commands[1], "Node.Ping", node, &rubbish); err != nil {
						log.Printf("Server unreachable: %v", err)
					} else {
						fmt.Println("Server responded")
					}
				}
			case "put":
				if len(commands) == 3 {
					var item Accept
					item.Slot = node.HighestSlot
					item.Command = line
					item.Tag = node.Address
					if err := Propose(node, item); err != nil {
						log.Println("Couldn't set key-value pair")
					} else {
						fmt.Println("Done")
					}
				} else {
					fmt.Println("Usage: put <key> <value>")
				}
			case "get":
				if len(commands) == 2 {
					var item Accept
					item.Slot = node.HighestSlot
					item.Command = line
					item.Tag = node.Address
					if err := Propose(node, item); err != nil {
						log.Println("Couldn't get key-value pair")
					} else {
						fmt.Println("Done")
					}
				} else {
					fmt.Println("Usage: get <key>")
				}
			case "delete":
				if len(commands) == 2 {
					var item Accept
					item.Slot = node.HighestSlot
					item.Command = line
					item.Tag = node.Address
					if err := Propose(node, item); err != nil {
						log.Println("Couldn't delete key-value pair")
					} else {
						fmt.Println("Done")
					}
				} else {
					fmt.Println("Usage: delete <key>")
				}
			case "dump":
				fmt.Println("=============")
				fmt.Println("Self: "+node.Address)
				fmt.Println("Highest Empty Slot:", node.HighestSlot)
				fmt.Println("Highest Accept:", node.HighestAccept.Slot, node.HighestAccept.Command)
				fmt.Println("Highest Prepare Sequence:", node.HighestPrepare)
				fmt.Println("Replicas:")
				for index := range node.Replicas {
					fmt.Println("\t"+string(node.Replicas[index]))
				}
				fmt.Println("History:")
				for index, value := range node.History {
					fmt.Printf("\t[%v]: %v\n",int(index), value)
				}
				fmt.Println("=============")
			default:
		}
	}
}
