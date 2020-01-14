# code team

def greeting():
    print('Welcome to Code Camp Team Manager')
    print('')
    print('This program will add teams to the team')
    print('database file. You can run the program')
    print('again to add more teams to the file.')
    print('')
    print('Use the other program to display a list of teams.')

def teamFileName():# name file, add team name, call teamMemberName
    filename = input('What is your team file name? ')
    fout = open(filename, 'a')
    add= 'y'
    teamname= ''
    while add == "y":
        teamName = input('Team name? ')
        fout.write('Team \n'+ teamName + '\n')
        nameList = teamMemberName()
        for i in range(len(nameList)):
            if nameList[i] != '':
                fout.write("Member \n"+nameList[i]+"\n")
        add = input('Another team? (y for yes)')
    fout.close()
    return teamName

def teamMemberName():# add memberName to nameList
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

