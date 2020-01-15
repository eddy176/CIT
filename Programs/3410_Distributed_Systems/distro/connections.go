package main

import (
	"bufio"
	crand "crypto/rand"
	"crypto/sha256"
	"crypto/subtle"
	"encoding/base64"
	"fmt"
	"log"
	"net"
	"strconv"
	"strings"

	"golang.org/x/crypto/pbkdf2"
)

func handleConnection(conn net.Conn, inChannl chan inEvent, player *Player) {

	scanner := bufio.NewScanner(conn)
	fmt.Println(player.name, "logged in from ", conn.RemoteAddr())

	// call look - tell player where they are
	// doLook("look", player)

	go func() {
		for event := range player.Outputs {
			fmt.Fprintf(conn, event.Text)
		}
		// only when players close the channel
		fmt.Printf("Connection closed: %v", conn.RemoteAddr())
		fmt.Printf("Closing player's goroutine: %v", conn.RemoteAddr())

		conn.Close()
		return // ends the goroutine?
	}()

	for scanner.Scan() {
		line := scanner.Text()
		LCommand := strings.Fields(line)
		if len(LCommand) == 0 {
			fmt.Fprint(conn, "Please enter a command")

		} else if _, ok := commands[LCommand[0]]; ok == true {
			inevent := inEvent{LCommand, player, false}
			inChannl <- inevent
		} else {
			player.Printf("Invalid input\n")
		}
	}

	//prompt and read input
	fmt.Printf("Goroutine closing, shutting down connection: %v", conn.RemoteAddr())

	inChannl <- inEvent{strings.Fields("quit"), player, false}
	return
}

func acceptConnections(inChannl chan inEvent) { // handle indevidual connections
	ln, err := net.Listen("tcp", ":9001")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Server is listening...")
	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Fatal(err)
		}
		fmt.Printf("Connection: %v\n", conn.RemoteAddr())
		go func() {
			// login
			scan := bufio.NewScanner(conn)
			var name, passwrd string
			fmt.Fprintf(conn, "What is your name?:\n")
			for scan.Scan() {
				name = strings.Trim(scan.Text(), " ")
				if name == " " {
					fmt.Fprintf(conn, "Please try again")
					conn.Close()
					fmt.Println("Connection closed: ", conn.RemoteAddr())
					return
				}
				break
			}
			// get password
			fmt.Fprintf(conn, "Input password:\n")
			for scan.Scan() {
				passwrd = scan.Text()
				if len(passwrd) < 6 {
					fmt.Fprint(conn, "Password length must be at least 6 characters.\n")
					conn.Close()
					fmt.Println("Connection closed: ", conn.RemoteAddr())
					return
				}
				break
			}
			// make salt
			var mSalt bool
			if playa, ok := Players[name]; ok {

				s, err := base64.StdEncoding.DecodeString(playa.Salt)

				hash, err := base64.StdEncoding.DecodeString(playa.Hash)

				if err != nil {
					log.Fatal(err)
				}
				enteredPass := pbkdf2.Key([]byte(passwrd), s, 64*1024, 32, sha256.New)

				// compare hash with entered pass
				fmt.Printf("hash: %v\nenteredPass: %v\n", hash, enteredPass)
				if subtle.ConstantTimeCompare(hash, enteredPass) != 1 {
					fmt.Fprint(conn, "Incorrect password.\n")
					conn.Close()
					fmt.Printf("Incorrect login: %v\n", name)
					fmt.Printf("Connection Close: %v\n", conn.RemoteAddr())
					return
				}
				fmt.Fprintf(conn, "Welcome, %v!\n", name)
				mSalt = false
			} else { // new player
				fmt.Fprintf(conn, "Welcome to mud!\n")
				fmt.Printf("New player connected: %v", conn.RemoteAddr())
				mSalt = true
			}

			outputEvent := make(chan outEvent)
			player := Player{name, Rooms[3001], outputEvent}

			if mSalt {
				salt := make([]byte, 32)
				_, salterr := crand.Read(salt)
				if salterr != nil {
					log.Fatal(salterr)
				}
				// make saltl
				salt64 := base64.StdEncoding.EncodeToString(salt)
				// make hash
				hash1 := pbkdf2.Key([]byte(passwrd), salt, 64*1024, 32, sha256.New)
				hashstring := base64.StdEncoding.EncodeToString(hash1)
				// log in event > channel
				inChannl <- inEvent{[]string{name, salt64, hashstring, strconv.Itoa(len(Players))}, &player, true}
			}
			if playa, ok := ActivePlayers[name]; ok { // handle if player was already active
				player.location = playa.location
				fmt.Printf("%v has joined mud: %v", player.name, conn.RemoteAddr())
				// close previous player's connection and set it to nil
				close(playa.Outputs)
				playa.Outputs = nil
			}

			ActivePlayers[name] = &player
			go handleConnection(conn, inChannl, &player)
		}()
	}
}

// // use player.command, player.shutdownEvent, player.newPlayer events
// func handleReply(player *Player) {
// 	for { // blocked until an event is sent through the channel
// 		cmdEvent := <-player.Outputs
// 		// fmt.Println("RECEIVED FROM REPLYCHANNEL")
// 		if cmdEvent != nil {
// 			// fmt.Printf("\nHandleReply Command: %v\n", cmdEvent.Text)

// 			cmdEvent.player = player
// 			player.Outputs <- cmdEvent
// 			// fmt.Println("PLAYER.OUTPUT HOLDING COMMAND")

// 		} else {
// 			fmt.Println("Error in handleReply, event pointer nul")
// 		}
// 		for event := range player.Outputs {
// 			fmt.Fprintf(player.conn, event.Text)
// 			fmt.Fprintf(player.conn, "What do you do?:\n")
// 			if event.Text == "Closing connection" {
// 				return
// 			}
// 		}
// 	}
// }
