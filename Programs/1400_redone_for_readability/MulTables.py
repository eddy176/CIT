import random
import time

def multiplication():
    print("Welcome to Multiplication Quiz!")
    print()
    print("I'll ask you questions, and you answer them.")
    x = float(input("What number do you want to multiply? "))
    startTime = time.time()
    for i in range(13):
          answer = x * i
          string = "What is " + str(x) + " * " + str(i) + "?"
          useranswer = float(int(input(string)))
          print(answer)
          while useranswer != answer:
              print("Oops! Try again!")
              useranswer = int(input(string))  
          print("Good job! DJ is cool!")
    stopTime = time.time()
    t = stopTime - startTime
    print("It only took you " + str(t) + " seconds!")
    if t < 25:
        print("Great job! DJ is way cool!")
    elif t > 60:
        print("You can math, but with more mathing, you can be as cool as DJ!")
          
multiplication()
