package main

import (
	"fmt"
	"log"
	"strings"
	"time"
)

// Propose is not rpc
func Propose(node *Node, item Accept) error {
	var rubbish Nothing
	completedSlot := false
	for !completedSlot {
		fmt.Println("===== Beginning Proposal Loop =====")
		fmt.Println(">HighestSlot:", node.HighestSlot)
		var data Accept
		data.Slot = node.HighestSlot
		item.Slot = node.HighestSlot
		node.HighestAccept.Command = item.Command
		seenSequence := -1
		completedSequence := false
		for !completedSequence {
			data.Command = node.HighestAccept.Command
			item.Sequence = seenSequence + 1
			data.Sequence = seenSequence + 1
			node.HighestAccept.Sequence = seenSequence + 1
			totalOk := 0
			totalNo := 0
			for _, add := range node.Replicas {
				wait := ((node.Generator * 142431) % 300) + 440
				time.Sleep(time.Duration(wait) * time.Millisecond) // LATENCY
				var prepareOk Accept
				fmt.Println("Asking", add)
				if err := call(add, "Node.Prepare", data, &prepareOk); err != nil {
					log.Printf("Bad Prepare from %v. Must be dead. %v\n", add, err)
				} else {
					if prepareOk.Okay {
						totalOk ++
					} else {
						totalNo ++
						fmt.Printf("%v rejected for sequence# %v, command %v.\n", add, prepareOk.Sequence, prepareOk.Command)
						if prepareOk.Sequence > seenSequence {
							seenSequence = prepareOk.Sequence
						}
						if len(prepareOk.Command) > 0 {
							node.HighestAccept.Command = prepareOk.Command
						}
					}
				}
				if totalOk > len(node.Replicas)/2 || totalNo > len(node.Replicas)/2 {
					break
				}
			}

			if totalNo > len(node.Replicas)/2 {
				fmt.Println("Got a majority who declined. Retrying..")
				time.Sleep(200 * time.Millisecond)
				continue
			}
			fmt.Println("Got a prepare majority. Accepting..")
			var prepareOk Accept
			totalOk = 0
			totalNo = 0
			for _, add := range node.Replicas {
				wait := ((node.Generator * 36521) % 267) + 412
				time.Sleep(time.Duration(wait) * time.Millisecond) // LATENCY
				if err := call(add, "Node.Accept", data, &prepareOk); err != nil {
					log.Printf("Bad Accept from %v: Must be dead.", add)
				} else {
					if prepareOk.Okay {
						totalOk++
					} else {
						fmt.Printf("%v rejected for sequence %v (%v)\n", add, prepareOk.Sequence, prepareOk.Command)
						totalNo++
					}
				}
			}
			if totalOk > len(node.Replicas)/2 {
				fmt.Println("Got an accept majority. Deciding..")
				for _, add := range node.Replicas {
					if err := call(add, "Node.Decide", data, &rubbish); err != nil {
						log.Printf("Bad Decide from %v: Must be dead.", add)
					}
				}
				if data.Command == item.Command {
					completedSlot = true
				}
			} else {
				time.Sleep(200 * time.Millisecond)
			}
			completedSequence = true
		}
		node.HighestPrepare = -1
	}
	return nil
}

// Prepare is not an rpc
func (n *Node) Prepare(item Accept, response *Accept) error {
	n.lock.Lock()
	fmt.Println("=====", n.Address, "Preparing slot", item.Slot, "..")
	if item.Slot >= n.HighestSlot {
		if item.Sequence > n.HighestPrepare {
			fmt.Println("ACCEPTED: Sequence", item.Sequence, ">", n.HighestPrepare)
			n.HighestPrepare = item.Sequence
			n.HighestAccept.Command = item.Command
			response.Okay = true
		} else {
			fmt.Printf("REJECTED: Sequence %v <= %v\n", item.Sequence, n.HighestPrepare)
			*response = n.HighestAccept
			response.Sequence = n.HighestPrepare
			response.Command = ""
			response.Okay = false
		}
	} else {
		response.Command = n.History[item.Slot]
		if item.Command == n.History[item.Slot] {
			response.Okay = true
			fmt.Printf("ACCEPTED: Slot %v matches with \"%v\"\n", item.Slot, n.History[item.Slot])
		} else {
			response.Okay = false
			fmt.Printf("REJECTED: Slot %v already filled with \"%v\"\n", item.Slot, n.History[item.Slot])
		}
	}
	n.lock.Unlock()
	return nil
}

// Accept is not rpc
func (n *Node) Accept(item Accept, response *Accept) error {
	n.lock.Lock()
	fmt.Println("=====", n.Address, "Accepting..")
	if item.Sequence >= n.HighestPrepare {
		fmt.Println("Sequence", item.Sequence, ">= highest prepared", n.HighestAccept.Sequence)
		n.HighestPrepare = item.Sequence
		n.HighestAccept.Sequence = item.Sequence
		n.HighestAccept.Command = item.Command

		*response = n.HighestAccept
		response.Okay = true
	} else {
		fmt.Println("Sequence", item.Sequence, "NOT >= highest prepared", n.HighestAccept.Sequence)
		n.HighestAccept.Okay = false
		*response = n.HighestAccept
	}
	n.lock.Unlock()
	return nil
}

// Decide isn't an rpc
func (n *Node) Decide(item Accept, response *Nothing) error {
	n.lock.Lock()
	defer n.lock.Unlock()
	empty := "[Empty]"
	fmt.Println("=====", n.Address, "Deciding..")
	n.HighestPrepare = -1
	n.HighestAccept.Sequence = -1
	currentCommand := strings.Fields(item.Command)
	if len(n.History) == item.Slot {
		n.HighestSlot ++
		if item.Slot > 0 && n.History[item.Slot-1] == empty {
			n.History = append(n.History, empty)
		} else {
			n.History = append(n.History, item.Command)
		}
		switch currentCommand[0] {
		case "put":
			fmt.Println("Putting", currentCommand[1], currentCommand[2])
			n.Bucket[currentCommand[1]] = currentCommand[2]
		case "get":
			fmt.Printf("Got %v: %v\n", currentCommand[1], n.Bucket[currentCommand[1]])
		case "delete":
			delete(n.Bucket, currentCommand[1])
			fmt.Println("Deleted", currentCommand[1])
		default:

		}
	} else if len(n.History) < item.Slot {
		for i := 0; i < item.Slot+1; i++ {
			n.History = append(n.History, empty)
		}
	} else {
		if n.History[item.Slot] == empty {
			n.History[item.Slot] = item.Command
			n.HighestSlot ++
			if n.History[0] == empty {
				n.HighestSlot = 0
			}
		}
	}
	return nil
}
