package main

import (
	"log"
	"math/big"
)

// Post is a node method that puts a value in the dht at key
func (n *Node) Post(pair Pair, reply *Nothing) error {
	n.Lock.Lock()
	// delete key from the bucket
	n.Bucket[pair.Key] = pair.Value
	n.Lock.Unlock()
	return nil
}

// Ping is an exported method that just returns nil when received
func (n *Node) Ping(junk Nothing, response *Nothing) error {
	return nil
}

// Get is a node method that returns a value stored at key
func (n *Node) Get(key string, response *string) error {
	n.Lock.Lock()
	// get the keys from the bucket
	for i := range n.Bucket {
		if i == key {
			*response = n.Bucket[i]
		}
	}
	n.Lock.Unlock()
	return nil
}

// Delete is a node method that removes a value from the bucket
func (n *Node) Delete(key string, response *Nothing) error {
	n.Lock.Lock()
	//delete the key from the bucket
	delete(n.Bucket, key)
	n.Lock.Unlock()
	return nil
}

// Stabilize is a node method that calls GetPredecessor,
// between, and notify
func (n *Node) Stabilize(junk Nothing, response *Nothing) error {
	var predecessor string
	// call get predecessor
	if err := call(n.Successor, "Node.GetPredecessor", junk, &predecessor); err != nil {
		log.Printf("Connection with successor failed: %v", err)
		return err
	}
	if predecessor != "" {
		// call between
		if between(hashString(n.Address), hashString(predecessor), hashString(n.Successor), false) {
			n.Successor = predecessor
		}
	}
	// call notify
	if err := call(n.Successor, "Node.Notify", n.Address, &junk); err != nil {
		log.Printf("Couldn't notify successor: %v", err)
		return err
	}
	log.Printf("Notified successor: %v", n.Successor)
	return nil
}

// GetPredecessor is a node method that gets the current node's predecessor
func (n *Node) GetPredecessor(junk Nothing, response *string) error {
	n.Lock.Lock()
	*response = n.Predecessor
	n.Lock.Unlock()
	return nil
} // is in own goroutine

// Notify is a node method that notifies the successor that you are the new predecessor
func (n *Node) Notify(predecessor string, response *Nothing) error {
	n.Lock.Lock()
	if n.Predecessor == "" || between(hashString(n.Predecessor), hashString(predecessor), hashString(n.Address), false) {
		n.Predecessor = predecessor
	}
	n.Lock.Unlock()
	return nil
} // is in own goroutine

// FindSuccessor is a node method that updates its successor node
func (n *Node) FindSuccessor(id *big.Int, response *FoundNode) error {
	var val string
	oldVal := val
	if err := call(n.Successor, "Node.Get", id, &val); err != nil {
		log.Printf("findsuccessor node.get: %v", err)
	} else {
		if val != oldVal {
			response.Found = true
			response.Node = n.Successor
			log.Printf("Found Successor: %v", n.Successor)
		} else {
			n.ClosestPrecedingNode(id, &response.Node)
			log.Printf("else: Closest Preceding: %v", response.Node)

		}
	}
	return nil
}

// ClosestPrecedingNode is a node method that returns the
// next preceding node if the current one is invalid
func (n *Node) ClosestPrecedingNode(id *big.Int, response *string) error {
	*response = n.Successor
	log.Printf("Closest preceding: %v", n.Successor)
	return nil
}
