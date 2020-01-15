package main

import (
	"database/sql"
	"fmt"
	"log"
	"strconv"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

func readZones(tx *sql.Tx) error {
	stmt, err := tx.Query("SELECT id, name FROM zones")
	if err != nil {
		tx.Rollback()
	}
	defer stmt.Close()
	tx.Commit()
	for stmt.Next() {
		var id int
		var name string
		err = stmt.Scan(&id, &name)
		if err != nil {
			return fmt.Errorf("Error scanning zones from db: %v", err)
		}
		zone := &Zone{
			ID:   id,
			Name: name,
		}
		Zones[zone.ID] = zone
		// fmt.Printf("Zone: %v\n", &zone)
	}
	return nil
}

// new readAllRooms
func readAllRooms(tx *sql.Tx) error {
	// Rooms maps indexes to each Room pointer
	allRRows, err := tx.Query("SELECT id, zone_id, name, description FROM rooms;")
	if err != nil {
		tx.Rollback()
		return fmt.Errorf("Error reading the database in readAllRooms: %v", err)
	}
	defer allRRows.Close()
	tx.Commit()
	for allRRows.Next() {
		var id int
		var zoneID int
		var name string
		var description string
		err := allRRows.Scan(&id, &zoneID, &name, &description)
		if err != nil {
			return fmt.Errorf("Error scanning rooms in the database: %v", err)
		}
		var room *Room
		for v := range Zones {
			if Zones[v].ID == zoneID {
				room = &Room{ // HOW TO INITIALIZE STRUCTS TYPES
					ID:          id,
					ZoneID:      Zones[v].ID,
					Name:        name,
					Description: description,
				}
				Rooms[room.ID] = room // linking pointer to room
				break
			}
		}
	}
	err = allRRows.Err()
	if err != nil {
		return fmt.Errorf("Error in rows of rooms: %v", err)
	}
	return nil
}

// read exits
func readExits(tx *sql.Tx) error {
	allExits, err := tx.Query("SELECT from_room_id, to_room_id, direction, description FROM exits;")
	if err != nil {
		tx.Rollback()
		return fmt.Errorf("Error reading the database in readAllRooms: %v", err)
	}
	defer allExits.Close()
	tx.Commit()
	for allExits.Next() {
		var fromRoomID int
		var toRoomID int
		var direction string
		var description string
		err := allExits.Scan(&fromRoomID, &toRoomID, &direction, &description)
		if err != nil {
			return fmt.Errorf("Error scanning exits in the database: %v", err)
		}
		exit := Exit{
			To:          Rooms[toRoomID],
			Description: description,
		}
		if strings.Compare(direction, "n") == 0 {
			Rooms[fromRoomID].Exits[0] = exit
		} else if strings.Compare(direction, "e") == 0 {
			Rooms[fromRoomID].Exits[1] = exit
		} else if strings.Compare(direction, "w") == 0 {
			Rooms[fromRoomID].Exits[2] = exit
		} else if strings.Compare(direction, "s") == 0 {
			Rooms[fromRoomID].Exits[3] = exit
		} else if strings.Compare(direction, "u") == 0 {
			Rooms[fromRoomID].Exits[4] = exit
		} else if strings.Compare(direction, "d") == 0 {
			Rooms[fromRoomID].Exits[5] = exit
		}
	}
	err = allExits.Err()
	if err != nil {
		return fmt.Errorf("Error in rows of rooms: %v", err)
	}
	return nil
}

// ReadPlayers reads in players and makes a map key : info
func ReadPlayers(tx *sql.Tx) map[string]Info {
	Players = make(map[string]Info)
	pQuery, err := tx.Query("SELECT * FROM players")
	if err != nil {
		log.Fatal(err)
	}
	for pQuery.Next() {
		var id int
		var name string
		var salt string
		var hash string
		pQuery.Scan(&id, &name, &salt, hash)
		Players[name] = Info{name, salt, hash}
	}
	return Players
}

// 
func makePlayerEntry(tx *sql.Tx, name string, salt string, hash string, numPlayers string) {
	id, err := strconv.Atoi(numPlayers)
	if err != nil {
		log.Fatal(err)
	}
	id++
	newid := strconv.Itoa(id)
	
	tx.Exec(`INSERT INTO players VALUES("$1", "$2", "$3", "$4")`, newid, name, salt, hash)
	Players[name] = Info{Name: name, Salt: salt, Hash: hash}
}
