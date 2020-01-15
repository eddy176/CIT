
def convert():
    raw_cube = input("input your cube with spaces: ")
    list_cube = raw_cube.split(' ')
    newlist = []
    for each in list_cube:
        newlist += list(each)
    return newlist
# print(convert())

def convert_cube(raw_cube):
    # raw_cube = input("input your cube with spaces: ")
    list_cube = raw_cube.split(' ')
    newlist = []
    for each in list_cube:
        newlist += list(each)
    return newlist

def cutString(goalCubeList):
    newlist = []
    for each in goalCubeList:
        for ch in each:
            newlist.append(ch)
    return newlist

# print(cutString(["wwwwwwwww", "gggggggg*", "rrrrrr*r*", "bbbbbb*b*", "oooooo*oo", "*y*yyyyy*"]))

def list_to_string(strlist):
    newstring = ""
    for each in strlist:
        newstring += each

    return newstring

print(list_to_string(["wwwwwwwww", "gggggggg*", "rrrrrr*r*", "bbbbbb*b*", "oooooo*oo", "*y*yyyyy*"]))
