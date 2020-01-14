
class Students:


    def __init__(self):
        self.sLine = []     # 1st turn: 1 single student
                            # 2nd turn: list with 2 students in it

    def file_len(self):
        with open("InsertNames.txt") as f:
            for i, l in enumerate(f):
                pass
        f.close()
        return i + 1

    def getInput(self):
        fin = open("InsertNames.txt", "r")
        for line in fin:
            line = line.split()
            for i in range(len(fin)):           # use a frickin while loop!! -> While fin is true!!! DUR!
                if self.sLine[2] == line[2]:
                    print("Error ")
                else:
                    self.sLine.append(line)
                    #print(str(line))
            self.sLine = line
        print(self.sLine)

    def getFName(self, sID):
        return self.sLine[sID][0]

    def getLName(self, sID):
        return self.sLine[sID][1]

    def getSN(self, sID):
        return self.sLine[sID][2]

    def getAge(self, sID):
        return self.sLine[sID][3]

    def setFName(self, sID, item):
        self.sLine[sID][0] = item

    def setLName(self, sID, item):
        self.sLine[sID][1] = item

    def setSNumber(self, sID,  item):
        self.sLine[sID][2] = item

    def setAge(self, sID, item):
        self.sLine[sID][3] = item

def main():
    boof = Students()
    boof.getInput()

main()
