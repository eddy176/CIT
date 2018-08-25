def create_monster_cast():
    monsters = {}
    return monsters

def add_cast_member(monsters, character, cast_member):
    monsters[character] = cast_member
    return monsters
def get_cast_member(monsters, character):
    return monsters[character]

def get_cast_size(monsters):
    return len(monsters)

def change_cast_member(monsters, character, cast_member):
    monsters[character] = cast_member
    return monsters

def has_character(monsters, character):
    for char in monsters:
        if char == characters:
            return True
        else:
            return False

def has_cast_member(monsters, cast_member):
    for char in monsters:
        if monsters[char] == cast_member
            return True
        else:
            return False

def get_longest_cast_member(monsters):
    longest = 0
    name = ''
    for va in monsters:
        if len(va) > longest:
            longest = len(va)
            name = monsters[longest]
    return name

def get_longest_character(monsters):
    newchar = ''
    for char in monsters:
        if len(char) > newchar:
            newchar = char
    return newchar

def get_character_of_longest_cast_member(monsters):
    longest = ''
    length = 1
    for key in monsters:
        if len(monsters.keys()) > length:
            longest = monsters[key]
    return longest





class Battery
    def __init__(self, capacity):
        self.mCapacity = capacity
        self.mBattery = capacity

    def getCapacity(self):
        return self.mCapacity

    def getCharge(self):
        return self.mBattery

    def drain(self, milliamps):
