# Game of Pig
import random
def greeting():
    print('Welcome to the Game of Pig. To win, be the')
    print('player with the most points at the end of the')
    print('game. The game ends at the end of a round where')
    print('at least one player has 100 or more points.')
    print('')
    print('On each turn, you may roll the die as many times')
    print('as you like to obtain more points. However, if')
    print('you roll a 1, your turn is over, and you do not')
    print('obtain any points that turn.')
    print('')
    print('Player 1 has 0 points.')
    print('Player 2 has 0 points.')
    print('')

def towin():
    p1score = 0
    p2score = 0
    while p1score <= 20 and p2score <= 20:# while players' score aren't > 99, keep playing
        p1score += turn()
        print('Player 1 score is',p1score,'.')
        p2score += turn()
        print('Player 2 score is',p2score,'.')
    if p1score > p2score:
        return 'Player 1'
    elif p2score > p1score:
        return 'Player 2'


    

def turn():
    pround = 0
    roll = 0
    while roll != 1 or pin != 'n':
        pin= input('(enter y to roll, n to stop). ')
        if pin == 'y':
            roll = roll_dice()
            if roll != 1:
                pround += roll
                print(pround)
            else:
                return 0
        elif pin == 'n' or pround == 0:
            return pround

def roll_dice():
    roll = random.randrange(1,7)
    print(roll)
    return roll

def win():
    winner = towin()
    print('Congrats',winner,'you won!')

def main():
    greeting()
    win()

main()
