import random
class Player:

    def __init__(self, name):
        self.mName = name
        letters = []
        self.mLetters = letters
        for i in range(7):
            self.drawLetter()
        return

    def getName(self):
        return self.mName

    def getLetters(self):
        return self.mLetters

    def drawLetter(self):
        letters = 'aaaaaaaaabbccddddeeeeeeeeeeeeffggghhiiiiiiiiijkllllmmnnnnnnooooooooppqrrrrrrssssttttttuuuuvvwwxyyz'
        newlet = random.choice(letters)
        self.mLetters.append(str(newlet))
        return str(newlet)

    def printLetters(self):
        hand = ''
        for i in range(len(self.mLetters)):
            hand += self.mLetters[i] + ' '
        return hand.strip()

    def checkWord(self,word):
        newl = ''
        userletters = self.mLetters[:]
        for char in word:
            if char in list(userletters):
                newl = userletters.pop(userletters.index(char))
            else:
                return False
        self.mLetters = userletters[:]
        return True