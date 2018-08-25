"""
Write your code in this file.

DO NOT RENAME THIS FILE
if you do, the unittests will not run.
"""
# open the file, read it, strip white space, then make a list of strings, return list.
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

# return the first string in the list, this is the candidate strand
def returnFirstString(strings):
    if len(strings) < 1:
        return ""
    else:
        return strings[0]

# check to make sure the strands are both longer than 0
def strandsAreNotEmpty(strand1, strand2):
    if len(strand1) > 0 and len(strand2) > 0:
        return True
    else:
        return False

# check to make sure the strands are equal in length, return if true or false
def strandsAreEqualLengths(strand1, strand2):
    if len(strand1) == len(strand2):
        return True
    else:
        return False

# take target and candidate, find largest overlap, return it
def findLargestOverlap(target, candidate):
    if strandsAreEqualLengths(target, candidate) != True or strandsAreNotEmpty(target, candidate) != True:
        return -1
    for i in range(len(target)):                #loop over the length of the target string
        tarslice = target[i:]                   #slice the target string from i to the end
        canslice = candidate[0:len(tarslice)]   #slice the candidate string from the beginning to the length of tarslice
        if tarslice == canslice:                #compare both slices to see if they match
            return len(tarslice)                #if they match, return the length of the slices
    return 0

# recieve target and candidates, determine which has largest overlap, keep first longest,
# return tuple containing largest overlap candidate with overlap. Return empty string and
# 0 for overlap if nothing overlaps
def findBestCandidate(target, candidates):
    bestcan = ""
    bestoverlap = 0
    for candidate in candidates:    # switch for loops?
        overlap = findLargestOverlap(target, candidate)
        if overlap > bestoverlap:
            bestoverlap = overlap
            bestcan = candidate
    return (bestcan, bestoverlap)
                
# takes target and candidate strings, cuts off overlap, adds them together into single
# string according to best candidate
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
    return woot

if __name__ == '__main__':
    main()
