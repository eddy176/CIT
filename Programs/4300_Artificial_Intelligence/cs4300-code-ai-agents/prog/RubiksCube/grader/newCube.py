
# wywywywyw gbgbgbgbg rorororor bgbgbgbgb ororororo ywywywywy
 
theCube = "wwwwwwwww bbbbgbbbb ooooroooo ggggbgggg rrrrorrrr yyyyyyyyy"
        #    wwwwwwwww bbbbgbbbb ooooroooo ggggbgggg rrrrorrrr yyyyyyyyy
#cube = ["wywywywyw" , "gbgbgbgbg" , "rorororor" , "bgbgbgbgb" , "ororororo" , "ywywywywy"]
def main ():
    #goalCube = ["wywywywyw" , "gbgbgbgbg" , "rorororor" , "bgbgbgbgb" , "ororororo" , "ywywywywy"]
    goalCube = theCube.split()
    #cube = convert_cube(cube)
    revCube = rev_Cube(goalCube[:])
    #revCube = convert_cube(revCube)
    goalCube = convert_cube(goalCube)
    revCube = convert_cube(revCube)

    f= open("definecubes.cmd","r")
    fout = open("definecubes1.cmd","w")
    for line in f:
        new_Cube = []
        line = line.strip()
        if len(line) == 0:
            continue
        l = line.split()
        if l[0] == "define" and l[1] == "cube" and len(l[3]) == 9:
            new_Cube = l[3:]
            #print(new_Cube)
        if (len(new_Cube) < 1):
            continue
        final_Cube = []
        #cube_List = []

        new_Cube = convert_cube(new_Cube)
        #print(new_Cube)        
        for i in range(len(new_Cube)):
            if new_Cube[4] == "w" :
                if new_Cube[i] == "*":
                    final_Cube.append("*")
                else :
                    final_Cube.append(goalCube[i])
            else:
                if new_Cube[i] == "*":
                    final_Cube.append("*")
                else :
                    final_Cube.append(revCube[i])
        string = l[0] +" " + l[1]+" " + l[2]+ " "
        fout.write(string)
        fout.write(list_to_string(final_Cube))
        fout.write("\n")
            

def rev_Cube(cube):
    swapCube = cube
    swapCube[0], swapCube[5], swapCube[1], swapCube[3] = swapCube[5], swapCube[0], swapCube[3], swapCube[1]
    for i in range(6):
        test = swapCube[i][-1::-1]
        swapCube[i] = test
    #print(swapCube)
    return swapCube


def convert_cube(raw_cube):
    newlist = []
    for each in raw_cube:
        newlist += list(each)
    return newlist

def list_to_string(strlist):
    #print(strlist)
    count = 0
    newstring = ""
    for i in range(54):
        count += 1
        newstring += strlist[i]
        if (count == 9):
            newstring += " "
            count = 0
    return newstring


main()