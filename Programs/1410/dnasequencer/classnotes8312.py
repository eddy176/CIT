import tower
[]
def main( ):
    t1 = tower.Tower( 1 )
    t2 = tower.Tower( 2 )
    t3 = tower.Tower( 3 )

    t1.loadDisk( 5 )
    t1.loadDisk( 3 )
    t1.loadDisk( 4 )
    t1.loadDisk( 2 )
    t1.loadDisk( 1 )

    disk = t3.removeDisk( )

    disk = t2.removeDisk( )
    return

main( )
