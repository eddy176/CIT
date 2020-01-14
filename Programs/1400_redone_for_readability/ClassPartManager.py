import random

def randomname():
    print("Welcome to Participation Manager!")
    print("")
    print("I'll read your roll file and randomly pick students for you.")
    print("")
    filename=input("What is the name of the roll file? ")
    fin=open(filename, "r")
    new=[]
    for line in fin:
        line=line.strip()
        new.append(line)
    x=input("")
    while x != "q":
        r=random.randrange(len(new))
        print(new[r])
        x=input("q for quit")
    fin.close()
randomname()
