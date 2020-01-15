package main

func addDCommand(command string, action func(string, *Player)) { // add all possible commands
	commands[command] = action // set the command as a key equal to the action passed in
}

func addCommand(command string, action func(string, *Player)) { // add all possible commands
	commands[command] = action // set the command as a key equal to the action passed in
}

func addCommands() {

	// non-default commands:
	addCommand("look", doLook)
	addCommand("loo", doLook)
	addCommand("lo", doLook)
	addCommand("l", doLook)
	
	// quit command:
	addCommand("quit", doQuit)

	// default commands:
	addDCommand("recall", recall)
	addDCommand("recal", recall)
	addDCommand("reca", recall)
	addDCommand("rec", recall)

	addDCommand("look", doLook)
	addDCommand("loo", doLook)
	addDCommand("lo", doLook)
	addDCommand("l", doLook)

	addDCommand("south", goSouth)
	addDCommand("sout", goSouth)
	addDCommand("Sou", goSouth)
	addDCommand("so", goSouth)
	addDCommand("s", goSouth)

	addDCommand("north", goNorth)
	addDCommand("nort", goNorth)
	addDCommand("nor", goNorth)
	addDCommand("no", goNorth)
	addDCommand("n", goNorth)

	addDCommand("east", goEast)
	addDCommand("eas", goEast)
	addDCommand("ea", goEast)
	addDCommand("e", goEast)

	addDCommand("west", goWest)
	addDCommand("wes", goWest)
	addDCommand("we", goWest)
	addDCommand("w", goWest)

	addDCommand("up", goUp)
	addDCommand("u", goUp)

	addDCommand("down", goDown)
	addDCommand("dow", goDown)
	addDCommand("do", goDown)
	addDCommand("d", goDown)

	// addDCommand("smile", doSmile)
	// addDCommand("smil", doSmile)
	// addDCommand("smi", doSmile)
	// addDCommand("sm", doSmile)

	// addDCommand("tell", doTell)
	// addDCommand("tel", doTell)
	// addDCommand("te", doTell)
	// addDCommand("t", doTell)

	addDCommand("say", doSay)
	// addDCommand("sa", doSay)


	addCommand("gossip", doGossip)
	// addCommand("gossi", doGossip)
	// addCommand("goss", doGossip)
	// addCommand("gos", doGossip)
	// addCommand("go", doGossip)
	// addCommand("g", doGossip)

}
