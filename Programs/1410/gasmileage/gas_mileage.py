import sys
def milesPerGallon(miles, gallons):
    total = 0
    if gallons != 0:
        total = miles / gallons
    return total
 
def createNotebook():
    notebook = []
    return notebook

def recordTrip(notebook, date, miles, gallons):
    trip = {}
    trip['date'] = date
    trip['miles'] = miles
    trip['gallons'] = gallons
    notebook.append(trip)
    return

def listTrips(notebook):
    if notebook == []:
        return []
    else:
        notebooklist = []
        for i in range(len(notebook)):
            date = notebook[i]['date']
            miles = notebook[i]['miles']
            gallons = notebook[i]['gallons']
            mpg = milesPerGallon(miles, gallons)
            notebooklist.append('On ' + str(date) + ': ' + str(miles) + ' miles traveled using ' + str(gallons) + ' gallons. Gas mileage: ' + str(mpg) + ' MPG.')
    return notebooklist

def calculateMPG(notebooklist):
    totalmiles = 0.0
    totalgallons = 0.0
    if notebooklist == 0:
        return 0.0
    else:
        for i in range(len(notebooklist)):
            tmiles = notebooklist[i]['miles']
            tgallons = notebooklist[i]['gallons']
            totalmiles += tmiles
            totalgallons += tgallons
            if totalmiles == 0.0 or totalgallons == 0.0:
                return 0.0
        return milesPerGallon(totalmiles, totalgallons)

def formatMenu():
    userinput = ['What would you like to do?', '[r] Record gas consumption', '[l] List mileage history', '[c] Calculate gas mileage', '[q] Quit']
    return userinput

def formatMenuPrompt():
    return "Enter an option: "

def getUserString(string):
    while True:
        entered = input(string).strip()
        if not entered:
            continue
        else:
            break
    return str(entered)

def getUserFloat(string):
    while True:
        try:
            num = input(string)
            num = float(num)
            if num > 0.0:
                return float(num)
            else:
                print("This number is not greater than zero")
        except ValueError:
            print("That is not in float format, please try again!")
    
def getDate():
    newdate = getUserString('Please enter a date. ')
    return newdate

def getMiles():
    newmiles = getUserFloat('Please enter miles in float form: ')
    while newmiles < 0:
        print("Miles cannot be negative, not even in reverse. Please try again. ")
        newmiles = getUserFloat('Please enter miles in float form: ')
    return newmiles
        
def getGallons():
    newgallons = getUserFloat('Please enter gallons in float form: ')
    while newgallons < 0:
        print("Gallons cannot be negative. Please try again. ")
        newgallons = getUserFloat('Please enter gallons in float form: ')
    return newgallons

def recordTripAction(notebook):
    date = getDate()
    miles = getMiles()
    gallons = getGallons()
    newtrip = recordTrip(notebook, date, miles, gallons)
    print("The trip was saved.")
    return

def listTripsAction(notebooklist):
    tripstrings = listTrips(notebooklist)
    if tripstrings == []:
        print("There aren't any trips recorded!")
    else:
        for i in tripstrings:
            print(i)
    return

def calculateMPGAction(notebooklist):
    calcaverage = calculateMPG(notebooklist)
    if calcaverage == 0.0:
        print("There is no trip data!")
    else:
        print("The average gas mileage is " + str(calcaverage) + 'mpg.')
    
def quitAction(notebook):
    print("This program will now shut down.")
    sys.exit( 0 )
    return
    
def applyAction(notebook,string):
    if string == 'r':
        recordTripAction(notebook)
    elif string == 'l':
        listTripsAction(notebook)
    elif string == 'c':
        calculateMPGAction(notebook)
    elif string == 'q':
        quitAction(notebook)
    else:
        print("Hey, that's not a proper input, dude.")
    return
def main():
    notebook = createNotebook()
    for line in formatMenu():
        line =line + "\n"
        print(line)
    print(formatMenuPrompt())
    string = getUserString('')
    while string != "q":
        applyAction(notebook,string)
        for line in formatMenu():
            line = line + "\n"
            print(line)
        print(formatMenuPrompt())
        string = getUserString('')
    
if __name__ == '__main__':
    main()

