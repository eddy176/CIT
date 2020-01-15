package main

import (
	"database/sql"
	"fmt"
	"log"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

// Rooms indexes to each room pointer
var Rooms = make(map[int]*Room)

// Zones maps indexes to each Zone pointer
var Zones = make(map[int]*Zone)

// Players is a map of Playa
var Players map[string]Info

// ActivePlayers is a map of active players
var ActivePlayers = make(map[string]*Player)

// commands is a map of command objects
var commands = make(map[string]func(string, *Player))

// for each room, keep a list of players, if the room is empty, it's a nul pointer

func main() {
	addCommands()
	fmt.Println("Commands loaded.")

	// open db at temple room
	db, err := sql.Open("sqlite3", "./world.db")
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	// send a transaction to readZones
	tx, err := db.Begin()
	if err != nil {
		log.Fatal(err)
	}
	err = readZones(tx)
	if err != nil {
		log.Fatal(err)
	}

	// send a transaction to ReadAllRooms
	tx, err = db.Begin()
	if err != nil {
		log.Fatal(err)
	}
	err = readAllRooms(tx)
	if err != nil {
		log.Fatal(err)
	}

	// send a transaction to readExits
	tx, err = db.Begin()
	if err != nil {
		log.Fatal(err)
	}
	err = readExits(tx)
	if err != nil {
		log.Fatal(err)
	}

	// send a transaction to get players
	tx, err = db.Begin()
	Players = ReadPlayers(tx)
	if err != nil {
		tx.Rollback()
		log.Fatalf("Failed to read the players from the database: %v", err)
	}
	tx.Commit()
	fmt.Print("Loaded game data.\n")

	inChannl := make(chan inEvent)

	go acceptConnections(inChannl)

	for event := range inChannl {
		if event.player.Outputs != nil {
			// login
			if event.login {
				tx, err := db.Begin()
				makePlayerEntry(tx, event.command[0], event.command[1], event.command[2], event.command[3])
				// if player wasn't successful
				if err != nil {
					tx.Rollback()
					log.Fatalf("Failure putting player in database: %v", err)
				}
				// if no errors
				tx.Commit()
				fmt.Printf("Logged in player: %v\n", event.player.name)
			} else {
				// accept commands
				commands[event.command[0]](strings.Join(event.command, " "), event.player)
			}
		}
	}
}
