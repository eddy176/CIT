import random
def instructions():
    print('Here are my awesome instructions')
    
def request_name(strnum):
    name = input("Please enter your name: ")
    return name

def greeting(name):
    print("Welcome,",name)

def roll_dice(sides):
    roll = random.randrange(1,sides+1)
    return roll

def roll_again(name):
    user = input(name+", do you want to roll? (1-roll, 2-quit) ")
    while user != "1" and user !="2":
        user = input(name+", do you want to continue (1-roll, 2-quit)? ")
    return user

def player_turn(string):
    total = 0
    ans= roll_again(string)
    if ans=="2":
        print(string,"has",total,"points")
        return total
    player1p=total
    player2p=total
    roll=roll_dice(6)
    while total < 20:
        while roll != 1 or ans != "2":
            roll=roll_dice(6)
            print(string,"rolled",roll)
            total += roll
            print(string,"has",total,"points")
            roll_again(string)
            #print(string,"rolled",roll)
            #total += roll
            #print(string,"has",total,"points")
                
    if roll == 1:
        print(string,"opps all your points are gone")
        total=0
        
    print(string,"has",total,"points")
    return total

def play_game(name1,name2):
    player1p= player_turn(name1)
    player2p= player_turn(name2)
    while player1p == player2_points:
        player1p= player_turn(name1)
        player2p= player_turn(name2)
    if player1p > player2_points:
        print(name1+" won")
    else:
        print(name2+" won")

def main():
    instructions()
    player1=request_name(1)
    player2=request_name(2)
    greeting(player1)
    greeting(player2)
    play_game(player1,player2)
main() 
