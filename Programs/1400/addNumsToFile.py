def addthensave(filename,numbers):
    fout = open(filename, 'a')
    total = 0
    for i in range(len(numbers)):
        total = total + numbers[i]
    fout.write(str(total) + '\n')
    fout.close()
addthensave("totalgoeshere.txt", [50,10,15,20])
