import sys
import random

def print_usage():
    print("Usage: python3 InstanceGenerator.py column row file-to-write-to")
    exit(1)

def main(argv):
    TellList = []
    try:
        columns = int(sys.argv[1])
    except:
        print_usage()
    try:
        rows = int(sys.argv[2])
    except:
        print_usage()
    try:
        filename = argv[3]
    except:
        print_usage()
    wumpusx = random.randrange(columns)
    wumpusy = random.randrange(rows)
    goldx = random.randrange(columns)
    goldy = random.randrange(rows)
    pitx = 0
    pity = 0
    while (wumpusx == wumpusy == 0):
        wumpusx = random.randrange(columns)
        wumpusy = random.randrange(rows)
    while (goldx == goldy == 0):
        goldx = random.randrange(columns)
        goldy = random.randrange(rows)
    TellList = [f'tell Wumpus_{wumpusx}_{wumpusy}\n'] + \
        [f'tell Gold_{goldx}_{goldy}\n'] + ['tell Player_0_0\n'] + \
        ['tell PlayerAlive\n'] + ['tell WumpusAlive\n'] + ['tell North\n'] + \
        ['tell !Grab\n']
    numpits = random.randrange((columns + rows) // 1.5)
    for i in range(columns):
        for j in range(rows):
            if i == j == 0:
                TellList.append(f'tell !Pit_{i}_{j}\n')
                continue
            if numpits != 0:
                # print("numpits didn't equal zero")
                choice = int(random.choice([0,1,2,4]))
                if choice % 2 == 1:
                    # print("choice was odd")
                    TellList.append(f'tell Pit_{i}_{j}\n')
                    numpits -= 1
                    continue
            TellList.append(f'tell !Pit_{i}_{j}\n')
    fout = open(filename, 'w')
    for line in TellList:
        fout.write(line)
    fout.close()


main(sys.argv)
