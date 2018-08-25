
# open the file, read it, strip white space, then make a list of strings, return list.
def fileToList(filename):
    f = open("filename" 'r')
    newlist = []
    for line in f:
        line=line.strip()
        if len(line) == 0:
            newlist += line
        else:
            newlist += line
        return newlist

# return the first string in the list, this is the candidate strand
def returnFirstString(strings):
    if len(strings) < 1:
        return strings[0]
    else:
        return strings[0]

# check to make sure the strands are both longer than 0
def strandsAreNotEmpty(strand1, strand2):
    if len(strand1) > 0 and len(strand2) > 0:
        return True
    else:
        return False

#check to make sure the strands are equal in length, return if true or false
def strandsAreEqualLengths(strand1, strand2):
    if len(strand1) == len(strand2):
        return True
    else:
        return False

# take target and candidate, find largest overlap, return it
def findLargestOverlap(target, candidate):
    overlaplen = 0
    for j in range(len(target)):
        for i in range(len(candidate)):
            if len(target) == len(candidate):
                if len(target) != 0:
                   if target[j] == candidate[i]:
                        overlaplen += 1
            else:
                return -1
    return overlaplen

# recieve target and candidates, determine which has largest overlap, keep first longest,
# return tuple containing largest overlap candidate with overlap. Return empty string and
# 0 for overlap if nothing overlaps
def findBestCandidate(target, candidates):
    tup1 = ();
    for candidate in candidates:    # switch for loops?
        for j in range(len(target)):
            if target[j:] == candidate[:-j]:
                if candidate[j] > candidate[:j]:# -i???
                   best
                else:
                   return tup1
                
# takes target and candidate strings, cuts off overlap, adds them together into single
# string according to best candidate
def joinTwoStrands(target, candidate, overlap):
    merge = ""
    merge = candidate[:overlap] + target[overlap:]
    return merge

def main():
    filename1 = input("Please input your dna target strand filename. ")
    filename2 = input("Please input your dna candidate strand filename. ")
    fileToList(filename1)
    fileToList(filename2)
    returnFirstString()
    strandsAreNotEmpty()
    strandsAreEqualLengths()
    findLargestOverlap()
    findBestCandidate()
    joinTwoStrands()

    if __name__ == '__main__':
        main()
