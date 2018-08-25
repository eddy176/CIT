string = 'aaacodebbb'
def count_code(string):
    c = 0
    for i in range(len(string)):
        if string[i] == 'c' and string[i+1] == 'o' and string[i+3] == 'e':
            c = c + 1
    print(c)
    return c
count_code(string)
