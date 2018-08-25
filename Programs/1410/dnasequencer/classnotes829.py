
def findLargestOverlap():
    #returns an integar(length or size of overlap)
    #

def findBestCandidate():
    #more overlap means better
    #most overlap = best
    #

def findlargest():
    storage = nums[0]
    for n in nums:
        if n > storage:
            storage = n
    return storage

# how is he going to keep track of his music?
# store data
# list of cds
# Status of a cd
# artist
# list of tracks
# song
    # name
    # length
    # genre
# search ripped files and insert


# architect/designer
    # designs the software
    # assigns the individual programs to each individual programmer
    # organizes the team and software

# class is a definition of things that are all similar
#       info and actions about a group of objects
# Data Members:: using variables inside a class
# title     string
# genre     string
# minutes   int
# seconds   int
# artist    string
#

class Song:
    def__init__( self, title, genre, minutes, seconds, artist ):#__init__ is defined inside of our class - this is called a method,
        self.mTitle = title             # if we build a class, python expects init(initialize) -constructor for the python class
        self.mGenre = genre
        self.mMinutes = minutes
        self.mSeconds = seconds
        self.mArtist = artist
        return

    def getTitle( self ): #call getTitle on self
        return self.mTitle

    def getArtist( self ):
        return self.mArtist

    def getGenre( self ):
        return self.mGenre


    def getMinutes(self):
        return self.mMinutes

    def setMinutes( self, minutes ):
        if minutes >= 0:
            self.mMinutes = minutes
        return


    def setSeconds(self, seconds):
        if seconds >= 0:
            self.mSeconds = seconds
        return