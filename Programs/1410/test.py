import time
def multiplication():
    print('Hello, welcome to multiplication tables!')
    print()
    n = input('What number would you like to multiply? ')
    t1 = time.time()
    num = int(n)
    for i in range(12):
        print(str(num), '*', str(i))
        answer = False
        t = num * i
        a = input('Please input an answer: ')
        ans = int(a)
        if ans == t:
            answer = True
        while answer == False:
            ans = input('Sorry, try again. ')
            if ans == t:
                answer = True
    t2 = time.time()
    endtime = t2 - t1
    if endtime < 20:
        print('Congrats, that took you', endtime, "seconds! You math masterfully!")
    elif endtime < 40 and endtime >= 20:
        print('Congrats, that took you', endtime, "seconds! You math sufficiently")
    elif endtime >= 40:
        print('That took you', endtime, "seconds. You can math, but you should probably practice mathing more.")
    else:
        print('....Dude, that took you', endtime, "seconds... I would ")
multiplication()