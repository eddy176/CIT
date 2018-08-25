import random
def createRandomList(size):
    a = []
    for i in range(size):
        a.append(random.randrange(0, 10))
    print(a)
    return a