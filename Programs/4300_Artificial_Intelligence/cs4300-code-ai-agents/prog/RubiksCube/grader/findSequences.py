import sys

def main(fname):
    mlist = []
    hdic = {}
    fin = open(fname, 'r')
    for line in fin:
        line = line.strip()
        line = line.strip('\\')
        line = line.split(' ')
        mlist += line
    for i in range(len(mlist)-4):
        for j in range(len(mlist)-4):
            if i == j:
                continue
            if mlist[i] == mlist[j] and mlist[i+1] == mlist[j+1] and mlist[i+2] == mlist[j+2]:
                if mlist[i] == mlist[j] and mlist[i+1] == mlist[j+1] and mlist[i+2] == mlist[j+2] and mlist[i+3] == mlist[j+3]:
                    if mlist[i] == mlist[j] and mlist[i+1] == mlist[j+1] and mlist[i+2] == mlist[j+2] and mlist[i+3] == mlist[j+3] and mlist[i+4] == mlist[j+4]:
                        try:
                            hdic[str(" ".join(mlist[i:i+5]))] += 1
                        except:
                            hdic[str(" ".join(mlist[i:i+5]))] = 1
                        i += 2
                        j += 2 
                        continue
                    try:
                        hdic[str(" ".join(mlist[i:i+4]))] += 1
                    except:
                        hdic[str(" ".join(mlist[i:i+4]))] = 1
                    i += 1
                    j += 1
                    continue
                try:
                    hdic[str(" ".join(mlist[i:i+3]))] += 1
                except:
                    hdic[str(" ".join(mlist[i:i+3]))] = 1
    for key in hdic:
        if hdic[key] >= 25:
            print("Command:", key, hdic[key])

main( str(sys.argv[1]) )