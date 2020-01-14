# Guess a Number
# Kacy Stocks
# Updated 5/14/2019 for readability
import random
def greeting():
    print("""
    Welcome to guess a number!
    I have chosen a number from 0 to 99.
    """)

def guess():
    num = random.randrange(0, 100)
    guessCount = 0
    guess = int(input("Guess a number " ))
    while guess != num:
        if guess > num:
            print("Nope, too high! Try again!")
            guessCount += 1
        elif guess < num:
            print("Nope. Too low! Try again!")
            guessCount += 1
        elif guess >= 100:
            print("You are guessing too high, remember? It's less than 100.")
            guessCount += 1
        elif guess < 0:
            print("You are guessing too low, remember? It's above 0.")
            guessCount += 1
        guess = int(input("Guess a number " ))
    print("Good job, you guessed " + str(guess) + "!")
    return guessCount
 
def main():
    greeting()
    guesses = guess()
    print("It only took you", guesses, "tries!")
main()
