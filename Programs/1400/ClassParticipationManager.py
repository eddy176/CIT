import random
def greeting():
    print("Welcome to Participation Manager!")
    print("")
    print("I'll read your roll file and randomly pick")
    print("students for you.")

def roll():
    filename=input("What is the name of the roll file?")
    fin = open(filename, 'r')
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
    


def main():
    greeting()
    roll()

main()


