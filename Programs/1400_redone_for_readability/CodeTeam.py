# Code Team
# Kacy Stocks
# Updated 5/14/2019 for readability
def greeting():
    print("""
    Welcome to Code Camp Team Manager!
    This program will output a list of teams to a file.
    You may run the program again to append to the file.
    Please use the other program to display the list of teams.
    """)

def teamFileName():
    filename = input('What is your team file name? ')
    fout = open(filename, 'a')
    add= 'y'
    teamname= ''

    while add == "y":
        teamName = input('Team name? ')
        fout.write('Team ' + teamName + ':\n\tMembers: ')
        nameList = teamMemberName()

        for i in range(len(nameList)):
            if nameList[i] != '':
                fout.write("\n\t\t"+nameList[i])
        add = input('Another team? (y for yes)')
    fout.close()
    print("Thank you for using the Code Camp Team Manager!")

    return teamName

def teamMemberName():
    memberName = ''
    while memberName == '':
        memberName = input('Member name? ')
    nameList = [memberName]
    while len(nameList) <= 3 and memberName != '':
        memberName = input('Member name? ')
        nameList.append(memberName)
    return nameList
def main():
    greeting()
    teamName = teamFileName()
main()

