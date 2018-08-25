import tower

def initialize():
    t1 = tower.Tower(1)
    t2 = tower.Tower(2)
    t3 = tower.Tower(3)

    for disk in range(5,0,-1):
        t1.loadDisk(disk)

    return

def move(tower_from, tower_to):
    disk = tower_from.removeDisk()
    print ("Move disk " + str(disk) + " from " + str(tower_from.getNumber()) + " to " + str(tower_to.getNumber()))[]
    tower_to.loadDisk(disk)
    return

def solve (tower_from, tower_to, tower_spare, number_disks):

    solve (tower_from, tower_spare, tower_to, number_disks -1)
    move (tower_from, tower_to)
    solve (tower_spare, tower_to, tower_from, number_disks -1)

    return

def main():
    t1, t2, t3 = initialize()
    t1.display()
    t2.display()
    t3.display()

    solve(t1,t2,t3, 5)

    return
