def writemyname(filename, name):
    fout = open(filename, 'w')
    fout.write(name + '\n')
    fout.close()
writemyname("mynamegoeshere.txt", "DJ Holt")
