import random
def greeting():
    print("Welcome to guess a number!")
    print("I have chosen a number from 0 to 99.")

def guess():
    num = random.randrange(0, 100)
    random.randrange(0, 9)
    guesses = 0
    guessed = 0
    guessed = input("Guess a number " )
    while int(guessed) != num:
        if int(guessed) > num:
            print("Nope, too high! Try again!")
            guesses = guesses + 1
        elif int(guessed) < num:
            print("Nope. Too low! Try again!")
            guesses = guesses + 1
        elif int(guessed) >= 100:
            print("You are guessing too high.")
            guesses = guesses + 1
        elif int(guessed) < 0:
            print("You are guessing below the range.")
            guesses = guesses + 1
        guessed = input("Guess a number " )
    print("Good job, you guessed " + guessed + "!")
    return guesses

    
def result(guesses):
    print("Awesome Job!")
    print("It only took you " + str(guesses) + " times.")
    

def main():
    greeting()
    guesses = guess()
    result(guesses)

main()
