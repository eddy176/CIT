import song # as long as they are in the same directory, python can find them
def main():
    s1 = song.Song("Sandstorm", "Techno-pop", 3, 52, "Darude")# s1 and s2 both instances or objects of the class
    s2 = song.Song("Levitate", "Modern", 4, 1, "Hadouken") # to get inside of either, use s1 or s2

    s1.setMinutes( 4 )
    s2.setMinutes( 1 )

    print( s1.getTitle())
    print( s1.getMinutes())
    print()
    print(s2.getTitle())
    print( s2.getArtist())
    print( s2.getGenre())
    return
main()