import random
def heads_tails():
    count = 0
    r= random.randrange(0,2)
    while r != 1:
        count += 1
        r= random.randrange(0,2)
    print(count)
    return count
heads_tails()
