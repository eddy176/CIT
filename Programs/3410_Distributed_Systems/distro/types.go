package main

import (
	"fmt"
)

// Command is a struct that has a verb and a function
type Command struct {
	Verb     string
	Function func(string, Player)
}

// Zone struct has an id, name, and a room pointer list
type Zone struct {
	ID    int
	Name  string
	Rooms []*Room
}

// Room has an id, zone pointer, name, description, and exit list
type Room struct {
	ID          int
	ZoneID      int
	Name        string
	Description string
	Exits       [6]Exit
}

// Exit has a direction(to) and a description
type Exit struct {
	From        *Room
	To          *Room
	Description string
}

// Event is a struct that hold a *Player and an io.Reader
type outEvent struct {
	Text   string
	player *Player
}

type inEvent struct {
	command []string
	player  *Player
	login   bool
}

// Player has a name, location, and a channel
type Player struct {
	name     string
	location *Room
	Outputs  chan outEvent
	// command  string
	// conn     net.Conn
}

// Info is a struct of player login information
type Info struct {
	Name string
	Salt string
	Hash string
}

// Printf is a function pulled from Sprintf that sends output throut a channel
func (player *Player) Printf(form string, a ...interface{}) {
	msg := fmt.Sprintf(form, a...) // a is a slice of interface
	player.Outputs <- outEvent{Text: msg}
}
