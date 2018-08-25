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

def fileToList():################ takes leet file, turns it into leet list
    filename = input("Leet file name?")
    fin = open(filename, 'r')
    leetList = []
    for line in fin:
        line=line.strip()
        leetList.append(line)
    fin.close()
    return leetList
    

def translateChar(char):#################### takes leet list, compares it with leet letters and returns correstponding english letters at that index
    leet_letters = "48CD3FGHIJK1MN0PQR57UVWXYZ@bcd3fghijk1mn0pqr57uvwxyz"
    eng_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    for i in range(len(leet_letters)):
        if leet_letters[i] == char:
            engChar = eng_letters[i]
            return engChar
    return char

def writeNewFile(listOfLines):################### takes english characters and puts them into a new file
    filename2 = input("What would you like to name your new file?")
    fout = open(filename2, 'w')
    for line in listOfLines:
        engChar = ""
        for char in line:
            engChar += translateChar(char)
        fout.write(engChar + '\n')
    fout.close()
    

def main():################################# calls all other functions
    greeting()
    leetList = fileToList()
    writeNewFile(leetList)

main()
# def translateChar(c):
#     eng= "abcde"
#     leet= "@bcd3"
#     c = "3"
#     pos = -1# invalid index to show that you found something,(-1 is an invalid index)
#     for i in range(len(leet)):
#         if leet[i] == c:
#             pos = i
#     if pos == -1:
#         return c
#     else:
#         return eng[pos]
