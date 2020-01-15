package main

import (
	"fmt"
	"strings"
)

// ReadRoom allows player to read the current room
func ReadRoom(id int, rooms map[int]*Room, player *Player) {
	description := rooms[id].Name + "\n"
	description += rooms[id].Description + "\n"
	player.Printf(description)
	for _, item := range ActivePlayers {
		if item.location == rooms[id] && item != player {
			player.Printf("You see " + item.name + " standing here\n")
		}
	}
}

// implement movement
func goNorth(line string, player *Player) {
	// fmt.Printf("movin north %v\n", player.location.Description)
	eX := player.location.Exits[0]
	if eX.To != nil {
		player.location = eX.To
		ReadRoom(player.location.ID, Rooms, player)
	} else {
		player.Printf("There is not exit in that direction. ")
	}
}

func goEast(line string, player *Player) {
	eX := player.location.Exits[1]
	if eX.To != nil {
		player.location = eX.To
		ReadRoom(player.location.ID, Rooms, player)
	} else {
		player.Printf("There is not exit in that direction. ")
	}
}

func goWest(line string, player *Player) {
	eX := player.location.Exits[2]
	if eX.To != nil {
		player.location = eX.To
		ReadRoom(player.location.ID, Rooms, player)
	} else {
		player.Printf("There is not exit in that direction. ")
	}
}

func goSouth(line string, player *Player) {
	eX := player.location.Exits[3]
	if eX.To != nil {
		player.location = eX.To
		ReadRoom(player.location.ID, Rooms, player)
	} else {
		player.Printf("There is not exit in that direction. ")
	}
}

func goUp(line string, player *Player) {
	eX := player.location.Exits[4]
	if eX.To != nil {
		player.location = eX.To
		ReadRoom(player.location.ID, Rooms, player)
	} else {
		player.Printf("There is not exit in that direction. ")
	}
}

func goDown(line string, player *Player) {
	eX := player.location.Exits[5]
	if eX.To != nil {
		player.location = eX.To
		ReadRoom(player.location.ID, Rooms, player)
	} else {
		player.Printf("There is not exit in that direction. ")
	}
}

// look
func doLook(line string, player *Player) {

	lineList := strings.Fields(line)
	if len(lineList) < 2 {
		ReadRoom(player.location.ID, Rooms, player)
		return
	} else if lineList[1][0] == 'n' {
		eX := player.location.Exits[0]
		if eX.To == nil {
			player.Printf("There is no exit in that direction. ")
		} else {
			player.Printf(eX.Description)
		}
	} else if lineList[1][0] == 'e' {
		eX := player.location.Exits[1]
		if eX.To == nil {
			player.Printf("There is no exit in that direction. ")
		} else {
			ReadRoom(player.location.ID, Rooms, player)
			player.Printf(eX.Description)
		}
	} else if lineList[1][0] == 'w' {
		eX := player.location.Exits[2]
		if eX.To == nil {
			player.Printf("There is no exit in that direction. ")
		} else {
			player.Printf(eX.Description)
		}
	} else if lineList[1][0] == 's' {
		eX := player.location.Exits[3]
		if eX.To == nil {
			player.Printf("There is no exit in that direction. ")
		} else {
			player.Printf(eX.Description)
		}
	} else if lineList[1][0] == 'u' {
		eX := player.location.Exits[4]
		if eX.To == nil {
			player.Printf("There is no exit in that direction. ")
		} else {
			player.Printf(eX.Description)
		}
	} else if lineList[1][0] == 'd' {
		eX := player.location.Exits[5]
		if eX.To == nil {
			player.Printf("There is no exit in that direction. ")
		} else {
			player.Printf(eX.Description)
		}
	} else {
		fmt.Println("doLook not working")
	}
}

// recall
func recall(line string, player *Player) {
	player.location = Rooms[3001]
	player.Printf("The world shifts and you are back where you started.\n")
	for _, item := range ActivePlayers {
		if item != player && item.location == player.location {
			item.Printf(player.name + " appears suddenly\n")
		}
	}
}

// func doSmile(line string, player *Player) {
// 	player.Printf("You smile %s\n", line)
// }

func doSay(line string, player *Player) {
	line = strings.TrimPrefix(line, "say ")
	for _, item := range ActivePlayers {
		if item.location == player.location && item.name != player.name {
			item.Printf("%s says, '%s'\n", player.name, line)
		}
	}
	player.Printf("You say, '%s'\n", line)
}

func doGossip(line string, player *Player) {
	line = strings.TrimPrefix(line, "gossip ")
	for _, item := range ActivePlayers {
		if item.name != player.name {
			item.Printf("%s gossips, '%s'\n", player.name, line)
		}
	}
	player.Printf("You gossip, '%s'\n", line)
}

// func doTell(line string, player *Player) {
// 	player.Printf("You tell %v\n", line)
// }

func doQuit(line string, player *Player) {
	player.Printf("Logging out\n")
	close(player.Outputs)
	fmt.Printf("Closing connection: %v", player.name)
	player.Outputs = nil
	delete(ActivePlayers, player.name)

	for _, item := range ActivePlayers {
		if item.location == player.location {
			item.Printf(player.name + " has left the game\n")
		}
	}
}
