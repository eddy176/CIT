import re

g_INTERFACE_NAMES = { "error": 0,
                      "plain": 1,
                      "rocks": 2,
                      "mud":   3,
                      "ice":   4,
                      "wall":  5,
                      "cliff": 6 }

g_INTERFACE_INDEXES = { 0: "error",
                        1: "plain",
                        2: "rocks",
                        3: "mud",
                        4: "ice",
                        5: "wall",
                        6: "cliff" }

class Cell:

    def __init__(self, id, x, y, z, neighbors, interfaces):
        self.id = id
        self.x = x
        self.y = y
        self.z = z
        self.neighbors  = [ neighbors[i] for i in range(len(neighbors)) ]
        self.interfaces = [ interfaces[i] for i in range(len(interfaces)) ]
        self.objects = []
        self.bases   = []
        self.goals   = []
        return

    def addObject(self, object_id):
        self.objects.append(object_id)
        return

    def addBase(self, base_id):
        self.bases.append(base_id)
        return

    def addGoal(self, goal_id):
        self.goals.append(goal_id)
        return

    def __str__(self):
        global g_INTERFACE_INDEXES
        parameters = [ self.id, self.x, self.y, self.z ]
        parameters.extend(self.neighbors)
        parameters.extend( [ str(g_INTERFACE_INDEXES[i]) for i in self.interfaces ] )
        s = "Cell: %d %.02f %.02f %.02f %d %d %d %d %s %s %s %s" % tuple(parameters)
        return s
    

class Object:

    def __init__(self, id, cell_id, name, value, kind, mass, volume, color, shape, size, lumin):
        self.id = id
        self.cell_id = cell_id
        self.name = name
        self.value = value
        self.kind = kind
        self.mass = mass
        self.volume = volume
        self.color = color
        self.shape = shape
        self.size = size
        self.lumin = lumin
        return
    
    def __str__(self):
        s = "Object: %s %d %s %.02f %s %.02f %.02f %s %s %s %s" % (self.id,
                                                                   self.cell_id,
                                                                   self.name,
                                                                   self.value,
                                                                   self.kind,
                                                                   self.mass,
                                                                   self.volume,
                                                                   self.color,
                                                                   self.shape,
                                                                   self.size,
                                                                   self.lumin)
        return s

class Base:

    def __init__(self, cell_id):
        self.cell_id = cell_id
        return
    
    def __str__(self):
        s = "Base: %d" % (self.cell_id)
        return s

class Goal:

    def __init__(self, cell_id):
        self.cell_id = cell_id
        return

    def __str__(self):
        s = "Goal: %d" % (self.cell_id)
        return s

class Interface:

    def __init__(self, title, damage, energy, traversable, is_fall):
        self.title = title
        self.damage = damage
        self.energy = energy
        self.traversable = traversable
        self.is_fall = is_fall
        return

    def __str__(self):
        s = "Interface: %s %d %d %d %d" % (self.title,
                                           self.damage,
                                           self.energy,
                                           self.traversable,
                                           self.is_fall)
        return s

    
class WorldData:

    def __init__(self):
        self.filename = "world.txt"
        self.readFile(self.filename)
        return

    def writeFile(self, filename):
        f = open(filename, "w")
        for i in self.interfaces.itervalues():
            f.write(str(i) + "\n")
        for c in self.cells.itervalues():
            f.write(str(c) + "\n")
        for o in self.objects.itervalues():
            f.write(str(o) + "\n")
        for b in self.bases:
            f.write(str(b) + "\n")
        for g in self.goals:
            f.write(str(g) + "\n")
        f.close()
        return
        
    def readFile(self, filename):
        self.cells = {}
        self.objects = {}
        self.bases = []
        self.goals = []
        self.interfaces = {}
        self.max_x = -1e12
        self.min_x =  1e12
        self.max_y = -1e12
        self.min_y =  1e12
        self.max_z = -1e12
        self.min_z =  1e12
        f = open(filename, "r")
        #Cell: 1492 -15000.00 -15000.00   -247.66 3414    0 1499    0  plain   wall  plain   wall
        #                     id          x             y               z          Nid    Sid     Eid     Wid     N          S          E          W
        cell_re = r'Cell:\s+(\d+)\s+(-?\d+\.\d+)\s+(-?\d+\.\d+)\s+(-?\d+\.\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+([^\s]+)\s+([^\s]+)\s+([^\s]+)\s+([^\s]+)'

        #Object: OBJ1 1492 pqt -14.00 mineral 0.49 1.75 pink box tiny
        #                       id         cell_id sn         value          kind        mass         volume       color      shape      size       lumin
        object_re = r'Object:\s+(OBJ\d+)\s+(\d+)\s+([^\s]+)\s+(-?\d+\.\d+)\s+([^\s+]+)\s+(\d+\.\d+)\s+(\d+\.\d+)\s+([^\s]+)\s+([^\s]+)\s+([^\s]+)(\s+([^\s]+))?'
        #Base: 420
        #                   #cell_id
        base_re = r'Base:\s+(\d+)'
        #Goal: 420
        #                   #cell_id
        goal_re = r'Goal:\s+(\d+)'
        #Interface: plain      0      0           1       0
        #                             interface  damage  energy  trav    fall
        interface_re = r'Interface:\s+([^\s]+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)'
        # comment/blank line
        comment_re = r'^\s*(#.*)?$'
        for line in f:
            match = re.search(cell_re, line)
            if match:
                id = int(match.group(1))
                x = float(match.group(2))
                y = float(match.group(3))
                z = float(match.group(4))
                neighbors = [ int(match.group(i)) for i in range(5,9) ] 
                interfaces = [ self.interfaceNameToIndex(str(match.group(i))) for i in range(9,13) ] 
                cell = Cell(id,x,y,z,neighbors,interfaces)
                self.cells[id] = cell
                if x < self.min_x: self.min_x = x
                if x > self.max_x: self.max_x = x
                if y < self.min_y: self.min_y = y
                if y > self.max_y: self.max_y = y
                if z < self.min_z: self.min_z = z
                if z > self.max_z: self.max_z = z
                continue

            match = re.search(object_re, line)
            if match:
                id      = str(match.group(1))
                cell_id = int(match.group(2))
                name    = str(match.group(3))
                value   = float(match.group(4))
                kind    = str(match.group(5))
                mass    = float(match.group(6))
                volume  = float(match.group(7))
                color   = str(match.group(8))
                shape   = str(match.group(9))
                size    = str(match.group(10))
                lumin   = str(match.group(11))
                if lumin == "None":
                    lumin = ""
                obj = Object(id, cell_id, name, value, kind, mass, volume, color, shape, size, lumin)
                self.objects[id] = obj
                self.cells[cell_id].addObject(id)
                continue
            
            match = re.search(base_re, line)
            if match:
                cell_id = int(match.group(1))
                base = Base(cell_id)
                self.cells[cell_id].addBase(len(self.bases))
                self.bases.append(base)
                continue
                
            match = re.search(goal_re, line)
            if match:
                cell_id = int(match.group(1))
                goal = Goal(cell_id)
                self.cells[cell_id].addGoal(len(self.goals))
                self.goals.append(goal)
                continue
                
            match = re.search(interface_re, line)
            if match:
                title       = str(match.group(1))
                damage      = int(match.group(2))
                energy      = int(match.group(3))
                traversable = int(match.group(4))
                is_fall     = int(match.group(5))
                interface = Interface(title, damage, energy, traversable, is_fall)
                self.interfaces[title] = interface
                continue

            match = re.search(comment_re, line)
            if match:
                # ignore comments and blank lines
                continue
                
            print 'NOMATCH:', line

        f.close()
        return
    
    def interfaceNameToIndex(self, name):
        global g_INTERFACE_NAMES
        if g_INTERFACE_NAMES.has_key(name):
            return g_INTERFACE_NAMES[name]
        print "ERROR: '%s'" % (name)
        return 0
    
    def getXRange(self):
        return self.min_x, self.max_x
    
    def getYRange(self):
        return self.min_y, self.max_y

    def getZRange(self):
        return self.min_z, self.max_z

    def getCells(self):
        return self.cells

    def getCell(self, cell_id):
        return self.cells[cell_id]
    
    def getObjects(self):
        return self.objects

    def getObject(self, object_id):
        return self.objects[object_id]
    
    def getBases(self):
        return self.bases

    def getBase(self, base_index):
        return self.bases[base_index]
    
    def getGoals(self):
        return self.goals

    def getGoal(self, goal_index):
        return self.goals[goal_index]
    
    def getInterfaces(self):
        return self.interfaces

    def getInterface(self, interface_id):
        return self.interfaces[interface_id]
    
