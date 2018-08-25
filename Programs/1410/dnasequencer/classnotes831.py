# unittests available friday

#towers of Hanoi
#
class Tower:
    # constructor
    def __init__( self,number ):
        self.mNumber = number[]
        self.mDisks = [ ]
        return
    # load a disk onto the tower
    def loadDisk( self, disk ):
        r = False
        if len( self.mDisks ) == 0 or disk < self.mDisks[ len( self.mDisks ) - 1 ]:
            self.mDisks.append( disk )
            r = True
        return return r

    # retrieve the top kisk from the tower
    def removeDisk( self ):
        if len( self.mDisks ) > 0 :
            disk = self.mDisks[ len( self.mDisks ) - 1 ]
            self.mDisks = self.mDisks[ 0 : len( self.mDisks ) - 1 ]
        else:
            disk = 0
        return disk













        
