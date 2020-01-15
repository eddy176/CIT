import os

def fileToList(filename):
    if not os.path.exists(filename):
        return []
    f = open(filename, 'r')
    t = []
    for line in f:
        line = line.strip()
        t.append(line)
    f.close()
    return t

def returnFirstString(strings):
    if len(strings) < 1:
        return ""
    else:
        return strings[0]

def strandsAreNotEmpty(strand1, strand2):
    if len(strand1) > 0 and len(strand2) > 0:
        return True
    else:
        return False

def strandsAreEqualLengths(strand1, strand2):
    if len(strand1) == len(strand2):
        return True
    else:
        return False

def findLargestOverlap(target, candidate):
    if strandsAreEqualLengths(target, candidate) != True or strandsAreNotEmpty(target, candidate) != True:
        return -1
    for i in range(len(target)):
        tarslice = target[i:]
        canslice = candidate[:len(tarslice)]
        if candidateOverlapsTarget(target, candidate, len(tarslice)):                
            return len(tarslice)
    return 0

def candidateOverlapsTarget(target, candidate, overlap):
    return target[-overlap:] == candidate[:overlap]


def findBestCandidate(target, candidates):
    bestcan = ""
    bestoverlap = 0
    for candidate in candidates:
        overlap = findLargestOverlap(target, candidate)
        if overlap > bestoverlap:
            bestoverlap = overlap
            bestcan = candidate
    return (bestcan, bestoverlap)
                
def joinTwoStrands(target, candidate, overlap):
    merge = ""
    merge = target + candidate[overlap:]
    return merge

def main():
    filename1 = input("Please input your dna target strand filename. ")
    filename2 = input("Please input your dna candidate strand filename. ")
    targetList = fileToList(filename1)
    candidateList = fileToList(filename2)
    target = returnFirstString(targetList)
    candidate = findBestCandidate(target, candidateList)
    best = candidate[0]
    overlap = candidate[1]
    woot = joinTwoStrands(target, best, overlap)
    print (woot)

if __name__ == '__main__':
    main()
