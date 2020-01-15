package main

import (
	"fmt"
	"net"
)

func getLocalAddress() string {
	var localaddress string

	ifaces, err := net.Interfaces()
	if err != nil {
		panic("init: failed to find network interfaces")
	}
	for _, elt := range ifaces {
		if elt.Flags&net.FlagLoopback == 0 && elt.Flags&net.FlagUp != 0 {
			addrs, err := elt.Addrs()
			if err != nil {
				panic("init: failed to get addresses for network interface")
			}

			for _, addr := range addrs {
				if ipnet, ok := addr.(*net.IPNet); ok {
					if ip4 := ipnet.IP.To4(); len(ip4) == net.IPv4len {
						localaddress = ip4.String()
						break
					}
				}
			}
		}
	}
	if localaddress == "" {
		panic("init: failed to find non-loopback interface with valid address on this node")
	}

	return localaddress
}
func printCommands() {
	fmt.Println("===Commands===")
	fmt.Println("quit")
	fmt.Println("help")
	fmt.Println("port <port>")
	fmt.Println("create")
	fmt.Println("ping")
	fmt.Println("join <address>")	
	fmt.Println("dump")
	fmt.Println("==============")
}
