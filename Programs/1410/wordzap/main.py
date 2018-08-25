import player

def getPlayers():
    newlist = []
    num_players = getUserInt('How many players?')
    count = 0
    while count != num_players:
        name = getUserString('Please enter the name for a player: ')
        game = player.Player(name)
        newlist.append(game)
        count += 1
    return newlist

def getUserString(string):
    entered = input(string).strip()
    return str(entered)

def getUserInt(string):
    while True:
        try:
            num = input(string)
            num = int(num)
            if num > 0:
                return int(num)
            else:
                print("This number is not greater than zero")
        except ValueError:
            print("That is not in proper format, please try again!")

def getLower(word):
    return word.lower()

def main():
    print('Welcome to Word Zap!')
    print('The first player that uses all of their letters wins!')
    print('')
    players = getPlayers()
    game_over = False
    while game_over == False:
        for i in range(len(players)):
            print(players[i].getName() + " it's your turn!")
            print(players[i].printLetters())
            nextturn = False
            while nextturn == False:
                user_word = getUserString('Enter a word to play(or press enter to pass)')
                if user_word == '':
                    let = players[i].drawLetter()
                    print("You get another letter: " + str(let) + '.')
                    nextturn = True
                else:
                    user_word = getLower(user_word)
                    nextturn = players[i].checkWord(user_word)
                    if nextturn == False:
                        print('Check your letters and try again!')
                        print(players[i].getLetters())
                    else:
                        print('Great Job!')
                        print('')
            if len(players[i].printLetters()) == 0:
                print(players[i].getName() + " wins!")
                game_over = True
                break

if __name__ == '__main__':
    main()