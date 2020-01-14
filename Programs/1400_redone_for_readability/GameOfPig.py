# Game of Pig
# Kacy Stocks
# Updated 5/14/2019 for readability
import random
def greeting():
    print("""
    Welcome to the Game of Pig. To win, be the player with the most points at the end of the game.
    The game ends at the end of the round where at least one player has reached the minimum ammount of winning points.
    On each turn, roll the die as many times as you like to obtain more points.
    If you roll a 1, your turn is over and you lose all your points that turn.
    Player 1 has 0 points.
    Player 2 has 0 points.
    """)

def towin():
    winscore = 20
    default = input("If you would like to keep the default win score of 20, press enter. Otherwise input custom win score. ")
    if default != '':
        winscore = int(default)
    p1score = 0
    p2score = 0
    print("Player 1, it's your turn! Remember, you must reach", winscore, "to win!")
    while p1score <= winscore and p2score <= winscore:
        p1score += turn()
        print('Player 1 score is',p1score)
        print("")
        print("Player 2, it's your turn! Remember, you must reach", winscore, "to win!")
        p2score += turn()
        print('Player 2 score is',p2score)
        print("")
        if p2score < winscore:
            print("Player 1, it's your turn! Remember, you must reach", winscore, "to win!")

    if p1score > p2score:
        return 'Player 1'
    elif p2score > p1score:
        return 'Player 2'

def turn():
    currentRound = 0
    roll = 0
    pin = ''
    while roll != 1 and pin != 'n':
        print("Current turn score is", currentRound)
        pin = input("Press enter to roll or input n to stop. ")
        if pin == 'n':
            return currentRound
        roll = roll_dice()
        currentRound += roll
    return 0

def roll_dice():
    roll = random.randrange(1,7)
    print("You rolled", roll)
    return roll

def win():
    winner = towin()
    print('Congrats',winner,'you won!')

def main():
    greeting()
    win()
    print("Thank your for playing Pig!")
main()
