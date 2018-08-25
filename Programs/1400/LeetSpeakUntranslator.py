# Leet Speak Untranslator
def greeting():
    print("Welcome to the Leet Speak Translator!")
    print("If you have a file that is written in leet")
    print("speak, we can translate it back to normal")
    print("English for you.")
    print("")
    print("Just give me the name of the file you want")
    print("to have translated, and the name you want")
    print("for the translated file.")

def listOfLines():################
    filename = input("Leet file name?")
    fin = open(filename, 'r')
    lList = []
    for line in fin:
        line=line.strip()
        lList.append(line)
    fin.close()
    return lList

def loopOverLetters(char):####################
    leet_letters = "48CD3FGHIJK1MN0PQR57UVWXYZ@bcd3fghijk1mn0pqr57uvwxyz"
    eng_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    eChar = ""
    for j in range(len(leet_letters)):
        if char == leet_letters[j]:
            eChar = eng_letters[j]
            return eChar
            


def charTranslator(leetList):##################
    leet_letters = "48CD3FGHIJK1MN0PQR57UVWXYZ@bcd3fghijk1mn0pqr57uvwxyz"
    eng_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    elist = []
    for line in leetList:
        eString = ""
        for i in range(len(line)):
            char = line[i]
            print(char)
            eChar = loopOverLetters(char)
            print(eChar)
            eString += eChar
        elist.append(eString)
    return elist

def writeNewFile(eChar):###################
    filename2 = input("What would you like to name your new file?")
    fout = open(filename2, 'w')
    for char in eChar:
        fout.write(char + '\n')
    fout.close()

def main():#################################
    greeting()
    lList = listOfLines()
    elist = charTranslator(lList)
    writeNewFile(elist)

main()

        
#def loopOverLine(lString):##################
  #  lChar = ""
   # for char in lString:
    #    lChar += char
    #return lChar
