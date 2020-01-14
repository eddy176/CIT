# Leet Speak Translator
# Kacy Stocks
# Updated 05/14/2019 to add proper capitalization and for readability.
def greeting():
    print("""
    Welcome to the Leet Translator!
    If you have a file that is written in Leet, this program can translate it to English for you!
    """)

def fileToList():
    filename = input("Please input the Leet file to be translated: ")
    fin = open(filename, 'r')
    leetList = []
    for line in fin:
        line=line.strip()
        leetList.append(line)
    fin.close()
    return leetList
    
def translateChar(char):
    leet_letters = "48CD3FGHIJK1MN0PQR57UVWXYZ@bcd3fghijk1mn0pqr57uvwxyz"
    eng_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    for i in range(len(leet_letters)):
        if leet_letters[i] == char:
            engChar = eng_letters[i]
            return engChar
    return char

def writeNewFile(listOfLines):
    filename2 = input(
        "Please input what you would like to name your translated file: ")
    fout = open(filename2, 'w')
    up = True
    for line in listOfLines:
        engChar = ""
        for i in range(len(line)):
            if line[i] == '.' or line[i] == '!' or line[i] == '?':
                up = True
            if up and line[i] in "48CD3FGHIJK1MN0PQR57UVWXYZ@bcd3fghijk1mn0pqr57uvwxyz":
                engChar += translateChar(line[i])
                up = False
            else:
                engChar += translateChar(line[i]).lower()
        fout.write(engChar + '\n')
    fout.close()
    
def main():
    greeting()
    leetList = fileToList()
    writeNewFile(leetList)
main()
