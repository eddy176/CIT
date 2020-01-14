import sys
def createIndex():
    dictionary = {}
    return dictionary

def recordBook(dictindex, ISBN, booktitle):
    dictindex[ISBN] = booktitle
    return

def findBook(dictindex, ISBN):
    if ISBN in dictindex:
        title = dictindex[ISBN]
        return title
    else:
        return ""

def listBooks(dictindex):
    lstrings = []
    sequence = 1
    if dictindex != {}:
        for ISBN in dictindex:
            lstrings.append(str(sequence) + ") " + ISBN + ": " + dictindex[ISBN])
            sequence += 1
    return lstrings

def formatMenu():
    userinput = ['What would you like to do?', '[r] Record a Book', '[f] Find a Book', '[l] List all Books', '[q] Quit']
    return userinput

def formatMenuPrompt():
    input = ("Enter an option: ")
    return input

def getUserChoice(prompt):
    while True:
        entered = input(prompt).strip()
        if not entered:
            continue
        else:
            break
    return str(entered)

def getISBN():
    prompt = "ISBN? "
    return getUserChoice(prompt)

def getTitle():
    prompt = "title? "
    return getUserChoice(prompt)

def recordBookAction(dictindex):
    ISBN = getISBN()
    Title = getTitle()
    dictindex[ISBN] = Title
    return

def findBookAction(dictindex):
    isISBN = getISBN()
    if isISBN not in dictindex:
        print('Unknown book query.')
    else:
        print(dictindex[isISBN])
    return

def listBooksAction(dictindex):
    bookstrings = listBooks(dictindex)
    if bookstrings == '':
        print("There aren't any books in here!!! ")
    else:
        for i in bookstrings:
            print(i)
    return

def quitAction(dictindex):
    print("This program will now shut down.")
    sys.exit( 0 )
    return

def applyAction(dictindex,userinput):
    if userinput == 'r':
        recordBookAction(dictindex)
    elif userinput == 'f':
        findBookAction(dictindex)
    elif userinput == 'l':
        listBooksAction(dictindex)
    elif userinput == 'q':
        quitAction(dictindex)
    else:
        print("Hey, that's not a proper input, dude.")
    return

def main():
    dictionary = createIndex()
    for line in formatMenu():
        line =line + "\n"
        print(line)
    print(formatMenuPrompt())
    userinput = getUserChoice('')
    while userinput != "q":
        applyAction(dictionary,userinput)
        for line in formatMenu():
            line = line + "\n"
            print(line)
        print(formatMenuPrompt())
        userinput = getUserChoice('')
        

if __name__ == '__main__':
    main()







