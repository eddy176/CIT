import caloric_balance
import sys
def formatMenu():
    rinput = ['[f] Record Food Consumption', '[a] Record Physical Activity', '[q] Quit']
    return rinput

def formatMenuPrompt():
    return "Enter an option: "

def formatActivityMenu():
    aMenu = ['Choose an activity to record', '[j] Jump rope', '[r] Running', '[s] Sitting', '[w] Walking']
    return aMenu

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

def createCaloricBalance():
    gender = getUserString('Please enter your gender[f or m]: ')
    age = getUserFloat('Please enter your age: ')
    height = getUserFloat('Please enter your height: ')
    weight = getUserFloat('Please enter your weight: ')
    balance = caloric_balance.CaloricBalance(gender, age, height, weight)
    print('Your starting balance is ' + str(balance.getBalance()) + '!')
    return balance

def recordActivityAction(balance):
    fam = formatActivityMenu()
    for stuff in fam:
        print(stuff)
    string = getUserString(formatMenuPrompt())
    string = string.strip()
    if string != 'j' and string != 'r' and string != 's' and string != 'w':
        print('Not a valid choice.')
        return
    minutes = getUserFloat('Please enter how long in minutes: ')
    if string == 'j':
        balance.recordActivity(.074, minutes)
    elif string == 'r':
        balance.recordActivity(.095, minutes)
    elif string == 's':
        balance.recordActivity(.009, minutes)
    elif string == 'w':
        balance.recordActivity(.036, minutes)
    nb = balance.getBalance()
    print('Awesome! Your caloric balance has been updated to ' + str(nb) + '!')
    return

def eatFoodAction(balance):
    calories = getUserFloat('Please enter calories consumed: ')
    balance.eatFood(calories)
    b = str(balance.getBalance())
    print('Your new caloric balance is ' + b + '!')
    return

def quitAction(balance):
    print("This program will now shut down.")
    sys.exit(0)
    return

def applyAction(balance,string):
    if string == 'f':
        eatFoodAction(balance)
    elif string == 'a':
        recordActivityAction(balance)
    elif string == 'q':
        quitAction(balance)
    else:
        print("Hey, that's not a proper input, dude.")
    return

def main():
    balance = createCaloricBalance()
    for line in formatMenu():
        line = line + "\n"
        print(line)
    print(formatMenuPrompt())
    string = getUserString('')
    while string != "q":
        applyAction(balance, string)
        for line in formatMenu():
            line = line + "\n"
            print(line)
        print(formatMenuPrompt())
        string = getUserString('')


if __name__ == '__main__':
    main()