#!/usr/bin/env python

import random, math, os, copy, sys

CELL_SIZE = 1000

I_PLAIN = "plain"
I_MUD   = "mud"
I_ICE   = "ice"
I_ROCKS = "rocks"
I_WALL  = "wall"
I_CLIFF = "cliff"

class Object:

    def __init__(self, id, cell_id, name, value, type, mass, volume, color, shape, size, luminescence):
        self.m_id = id
        self.m_cell_id = cell_id
        self.m_name = name
        self.m_value = value
        self.m_type = type
        self.m_mass = mass
        self.m_volume = volume
        self.m_color = color
        self.m_shape = shape
        self.m_size = size
        self.m_luminescence = luminescence
        return

    def setId(self, id):
        self.m_id = id
        return
    
    def setCellId(self, cell_id):
        self.m_cell_id = cell_id
        return

    def __str__(self):
        s = "Object: %10s %6d %8s %8.2f %10s %8.2f %8.2f %20s %10s %10s %12s" % \
            (self.m_id, self.m_cell_id, self.m_name, self.m_value, self.m_type,
             self.m_mass, self.m_volume, self.m_color, self.m_shape, self.m_size, self.m_luminescence, )
        return s

    def __repr__(self):
        return self.__str__()

    @classmethod
    def read(cls, fin):
        line = fin.readline()
        if not fin or not line:
            return None
        line = line.strip()
        cols = line.split()
        cols.pop(0)
        id, cell_id, name, value, type, mass, volume = \
            cols[0], int(cols[1]), cols[2], float(cols[3]), cols[4], float(cols[5]), float(cols[6])
        color, shape, size, luminescence = cols[7], cols[8], cols[9], ""
        if len(cols) > 10:
            luminescence = cols[10]
        obj = cls(id, cell_id, name, value, type, mass, volume, color, shape, size, luminescence)
        return obj

    @classmethod
    def readFile(cls, file_name):
        objs = []

        if os.path.exists(file_name):
            fin = open(file_name, "r")
            obj = True
            while fin and obj:
                obj = cls.read(fin)
                if obj:
                    objs.append(obj)
            fin.close()

        return objs


class Origin:
    def __init__(self, name, value):
        self.m_name = name
        self.m_value = value
        return
    
    def getName(self):
        return self.m_name
    def getValue(self):
        return self.m_value
    def setValue(self, value):
        self.m_value = value
        return

class Trait:
    def __init__(self, name, symbol):
        self.m_name = name
        self.m_symbol = symbol
        return

    def getName(self):
        return self.m_name
    def getSymbol(self):
        return self.m_symbol

class Color(Trait):

    def __init__(self, name, symbol):
        Trait.__init__(self, name, symbol)
        return
    
class Shape(Trait):
    def __init__(self, name, type, symbol):
        Trait.__init__(self, name, symbol)
        self.m_type = type
        return

    def getType(self):
        return self.m_type

class Size(Trait):
    
    def __init__(self, name, min_mass, max_mass, min_volume, max_volume, symbol):
        Trait.__init__(self, name, symbol)
        self.m_min_mass = min_mass
        self.m_max_mass = max_mass
        self.m_min_volume = min_volume
        self.m_max_volume = max_volume
        return
        
    def getMass(self):
        return self.m_min_mass
    def getVolume(self):
        return self.m_min_volume


class Luminescence(Trait):

    def __init__(self, name, symbol):
        Trait.__init__(self, name, symbol)
        return
    
    
class ObjectBN:

    def __init__(self,
                 origins, origin_CPT,
                 colors, color_CPT,
                 shapes, shape_CPT,
                 sizes, size_CPT,
                 luminescences, luminescence_CPT
                 ):
        self.m_origins = origins
        self.m_origin_CPT = origin_CPT
        self.m_colors = colors
        self.m_color_CPT = color_CPT
        self.m_shapes = shapes
        self.m_shape_CPT = shape_CPT
        self.m_sizes = sizes
        self.m_size_CPT = size_CPT
        self.m_luminescences = luminescences
        self.m_luminescence_CPT = luminescence_CPT

        self.m_object_count = 0
        return

    def chooseOrigin(self):
        r = random.random()
        t = 0.0
        for i in range(len(self.m_origins)):
            t += self.m_origin_CPT[i]
            if r < t:
                return i
        return -1

    def chooseTrait(self, origin, CPT):
        r = random.random()
        t = 0.0
        for i in range(len(CPT[origin])):
            t += CPT[origin][i]
            if r < t:
                return i
        return -1
    
    def chooseColor(self, origin):
        return self.chooseTrait(origin, self.m_color_CPT)
    def chooseShape(self, origin):
        return self.chooseTrait(origin, self.m_shape_CPT)
    def chooseSize(self, origin):
        return self.chooseTrait(origin, self.m_size_CPT)
    def chooseLuminescence(self, origin):
        return self.chooseTrait(origin, self.m_luminescence_CPT)

    def createObject(self, use_luminescence):
        self.m_object_count += 1
        obj_id       = "OBJ%05d" % (self.m_object_count)
        cell_id      = 1
        origin       = self.chooseOrigin()
        color        = self.chooseColor(origin)
        shape        = self.chooseShape(origin)
        size         = self.chooseSize(origin)
        luminescence = self.chooseLuminescence(origin)
        name         = (self.m_colors[color].getSymbol() +
                        self.m_shapes[shape].getSymbol() +
                        self.m_sizes[size].getSymbol()
                        )
        value        = self.m_origins[origin].getValue()
        obj_type     = self.m_shapes[shape].getType()
        mass         = self.m_sizes[size].getMass()
        volume       = self.m_sizes[size].getVolume()
        
        if use_luminescence:
            name += self.m_luminescences[luminescence].getSymbol()
            l_str = self.m_luminescences[luminescence].getName()
        else:
            l_str = ""
            
        obj          = Object(obj_id, cell_id, name, value, obj_type, mass, volume,
                              self.m_colors[color].getName(),
                              self.m_shapes[shape].getName(),
                              self.m_sizes[size].getName(),
                              l_str)
        return obj



class ObjectEnumeration:

    def __init__(self,
                 colors,
                 shapes,
                 sizes,
                 luminescences,
                 combo_values
                 ):
        self.m_colors = colors
        self.m_shapes = shapes
        self.m_sizes = sizes
        self.m_luminescences = luminescences
        self.m_combo_values = combo_values

        self.m_object_count = 0

        self.m_names = {}
        return

    def chooseTrait(self, trait_list):
        return random.randrange(len(trait_list))
    def chooseColor(self):
        return self.chooseTrait(self.m_colors)
    def chooseShape(self):
        return self.chooseTrait(self.m_shapes)
    def chooseSize(self):
        return self.chooseTrait(self.m_sizes)
    def chooseLuminescence(self):
        return self.chooseTrait(self.m_luminescences)
    def chooseValue(self,color, shape, size, luminescence):
        for combo in self.m_combo_values:
            if combo[0] == color and combo[1] == shape and combo[2] == size and combo[3] == luminescence:
                return combo[4]
        return - self.m_combo_values[-1][4]

    def createObject(self, use_luminescence):
        max_possible = len(self.m_colors) * len(self.m_shapes) * len(self.m_sizes)
        if use_luminescence:
            max_possible *= len(self.m_luminescences)
        if self.m_object_count >= max_possible:
            print "Not enough unique object types."
            sys.exit(1)
            
        self.m_object_count += 1

        done = False
        while not done:
            obj_id       = "OBJ%05d" % (self.m_object_count)
            cell_id      = 1
            color        = self.chooseColor()
            shape        = self.chooseShape()
            size         = self.chooseSize()
            luminescence = self.chooseLuminescence()
            name         = (self.m_colors[color].getSymbol() +
                            self.m_shapes[shape].getSymbol() +
                            self.m_sizes[size].getSymbol())
            obj_type     = self.m_shapes[shape].getType()
            mass         = self.m_sizes[size].getMass()
            volume       = self.m_sizes[size].getVolume()
        
            if use_luminescence:
                name += self.m_luminescences[luminescence].getSymbol()
                l_str = self.m_luminescences[luminescence].getName()
            else:
                l_str = ""
                luminescence = 0

            value        = self.chooseValue(color, shape, size, luminescence)
            
            if not self.m_names.has_key(name):
                done = True
            
        obj          = Object(obj_id, cell_id, name, value, obj_type, mass, volume,
                              self.m_colors[color].getName(),
                              self.m_shapes[shape].getName(),
                              self.m_sizes[size].getName(),
                              l_str)
        
        self.m_names[name] = 1
        
        return obj


class Cell:

    def __init__(self, cell_id, x, y, z, interface):
        self.m_cell_id = cell_id
        self.m_x = x
        self.m_y = y
        self.m_z = z
        self.m_neighbors = [ 0, 0, 0, 0 ]
        self.m_interfaces = [ interface, interface, interface, interface ]
        self.m_objects = []
        return

    def addObject(self, obj):
        self.m_objects.append(obj)
        return

    def getPosition(self):
        return self.m_x, self.m_y

    def getCellId(self):
        return self.m_cell_id

    def merge(self, cell):
        # add hills, keep from growing too fast
        self.m_z += cell.m_z
        self.m_z /= 1.5       

        # don't allow too high, or too low
        if self.m_z > 1000:
            self.m_z = 1000
        if self.m_z < -1000:
            self.m_z = -1000
            
        # choose interfaces
        for i in range(len(self.m_interfaces)):
            if random.random() < 0.5:
                self.m_interfaces[i] = cell.m_interfaces[i]
                
        return

    def setNeighbor(self, direction, cell):
        self.m_neighbors[direction] = cell.m_cell_id
        # make interfaces consistent
        od = [ 1, 0, 3, 2 ]
        opposite_direction = od[direction]
        if self.m_interfaces[direction] != cell.m_interfaces[opposite_direction]:
            self.m_interfaces[direction] = cell.m_interfaces[opposite_direction]
        return

    def setWall(self, dx, dy):
        if dy > 0:
            i = 0
        elif dy < 0:
            i = 1
        elif dx > 0:
            i = 2
        elif dx < 0:
            i = 3
        self.m_interfaces[i] = I_WALL
        return

    def setCliffWall(self, dx, dy, cell, cliff_height):
        if dy > 0:
            i = 0
            i1 = 1
        elif dy < 0:
            i = 1
            i1 = 0
        elif dx > 0:
            i = 2
            i1 = 3
        elif dx < 0:
            i = 3
            i1 = 2
        
        if self.m_z - cell.m_z > cliff_height:
            self.m_interfaces[i] = I_CLIFF
            cell.m_interfaces[i1] = I_WALL
        elif cell.m_z - self.m_z > cliff_height:
            self.m_interfaces[i] = I_WALL
            cell.m_interfaces[i1] = I_CLIFF

        return
            
    def __str__(self):
        s = ""
        s = "Cell: %4d %9.2f %9.2f %9.2f %4d %4d %4d %4d %6s %6s %6s %6s" % ( \
            self.m_cell_id,
            self.m_x * CELL_SIZE, self.m_y * CELL_SIZE, self.m_z,
            self.m_neighbors[0], self.m_neighbors[1], self.m_neighbors[2], self.m_neighbors[3],
            self.m_interfaces[0], self.m_interfaces[1], self.m_interfaces[2], self.m_interfaces[3]
            )
        
        for o in self.m_objects:
            s += "\n" + str(o)
            
        return s

class Continent:

    def __init__(self, xc, yc, radius, elevation, hilliness, interface, first_cell_id):
        self.m_cell_id = first_cell_id
        self.m_cells = []
        for dy in range(-radius, radius+1):
            for dx in range(-radius, radius+1):
                dist = math.sqrt(float(dy*dy + dx*dx))/radius
                if dist > 1.0 and (random.random() > (2.0 - dist)):
                    continue # out of range, and dice roll fails

                x = xc + dx
                y = yc + dy
                z = elevation + random.random() * hilliness
                self.m_cells.append( Cell(self.m_cell_id, x, y, z, interface) )
                self.m_cell_id += 1

        return

    def getCellId(self):
        return self.m_cell_id

    def getCells(self):
        return self.m_cells

    def __str__(self):
        s = ""
        for c in self.m_cells:
            s += str(c) + "\n"
        return s

class World:

    def __init__(self, width, height, objects):
        self.m_width   = width
        self.m_height  = height
        self.m_objects = objects
        self.m_cells   = []
        self.m_cell_id = 1
        self.m_object_id = 1
        self.m_min_radius    = 3
        self.m_max_radius    = 10
        self.m_min_elevation = -1000
        self.m_max_elevation =  1000
        self.m_cliff_height  =   500
        self.m_hilliness     =    0.9 # percentage of cliff height
        self.m_percent_plain = 0.70
        self.m_percent_mud   = 0.20
        self.m_percent_ice   = 0.00

        self.m_num_base         = 1
        self.m_num_objects      = 5
        self.m_num_base_objects = 5
        
        self.m_finalized        = False
        for y in range(self.m_height+1):
            for x in range(self.m_width+1):
                self.m_cells.append( None )
        self.m_bases = [ None for i in range(self.m_num_base) ]
        self.m_goal = None
        return

    def setRadii(self, min_radius, max_radius):
        self.m_min_radius = min_radius
        self.m_max_radius = max_radius
        return

    def setPercentPlain(self, value):
        self.m_percent_plain = value
        return
    
    def setPercentMud(self, value):
        self.m_percent_mud = value
        return
    
    def setPercentIce(self, value):
        self.m_percent_ice = value
        return
    
    def setNumBase(self, num_base):
        self.m_num_base = num_base
        self.m_bases = [ None for i in range(self.m_num_base) ]
        return
    
    def setNumObjects(self, num_objects):
        self.m_num_objects = num_objects
        self.m_num_base_objects = num_objects
        return
    
    def setNumBaseObjects(self, num_base_objects):
        self.m_num_base_objects = num_base_objects
        return
        

    def index(self, x, y):
        return y * (self.m_width + 1) + x

    def inRange(self, x, y):
        return x >= 0 and x <= self.m_width and y >= 0 and y <= self.m_height

    def pickRandomInterface(self):
        r = random.random()
        if r < self.m_percent_plain:
            interface = I_PLAIN
        elif r < self.m_percent_plain + self.m_percent_mud:
            interface = I_MUD
        elif r < self.m_percent_plain + self.m_percent_mud + self.m_percent_ice:
            interface = I_ICE
        else:
            interface = I_ROCKS
        return interface

    def createRandomContinent(self):
        radius    = int( random.random() * (self.m_max_radius - self.m_min_radius + 1) + self.m_min_radius)
        elevation = random.random() * (self.m_max_elevation - self.m_min_elevation + 1) + self.m_min_elevation
        hilliness = random.random() * self.m_cliff_height * self.m_hilliness
        xc        = random.randrange(0, self.m_width+1)
        yc        = random.randrange(0, self.m_height+1)
        interface = self.pickRandomInterface()
        continent = Continent(xc, yc, radius, elevation, hilliness, interface, self.m_cell_id)
        self.m_cell_id = continent.getCellId()
        return continent


    def mergeContinent(self, continent):
        for cell in continent.getCells():
            x, y = cell.getPosition();
            if not self.inRange(x, y):
                continue  # out of range, ignore
            i = self.index(x, y)

            if self.m_cells[i]: # merge
                self.m_cells[i].merge(cell)
            else:               # set first time
                self.m_cells[i] = cell
        return
    
    def addRandomContinent(self):
        continent = self.createRandomContinent()
        self.mergeContinent(continent)
        return

    def linkCells(self):
        dx = [ 0, 0, 1, -1 ]
        dy = [ 1, -1, 0, 0 ]
        for y in range(self.m_height+1):
            for x in range(self.m_width+1):
                i = self.index(x, y)
                for j in range(len(dx)):
                    x1 = x + dx[j]
                    y1 = y + dy[j]
                    if not self.inRange(x1, y1):
                        continue  # out of range, ignore
                    k = self.index(x1, y1)
                    if self.m_cells[i] and self.m_cells[k]:
                        self.m_cells[i].setNeighbor(j, self.m_cells[k])
        return

    def findCliffs(self):
        dx = [ 0, 0, 1, -1 ]
        dy = [ 1, -1, 0, 0 ]
        for y in range(self.m_height+1):
            for x in range(self.m_width+1):
                i = self.index(x, y)
                if not self.m_cells[i]:
                    continue # no cell here
                for j in range(len(dx)):
                    x1 = x + dx[j]
                    y1 = y + dy[j]
                    k = self.index(x1, y1)
                    if (not self.inRange(x1, y1)) or (not self.m_cells[k]): # edge of world: wall
                        self.m_cells[i].setWall(dx[j], dy[j])
                    else:
                        self.m_cells[i].setCliffWall(dx[j], dy[j], self.m_cells[k], self.m_cliff_height)
        return

    def placeBases(self):
        base_count = 0
        while base_count < self.m_num_base:
            c = random.choice(self.m_cells)
            if c:
                if not c.getCellId() in self.m_bases:
                    self.m_bases[base_count] = c.getCellId()
                    base_count += 1
        return
    
    def placeGoal(self):
        while not self.m_goal:
            c = random.choice(self.m_cells)
            if c:
                if not c.getCellId() in self.m_bases:
                    self.m_goal = c.getCellId()
        return
    
    def placeObjects(self):
        if len(self.m_objects) <= 0:
            return
        for c in self.m_cells:
            if c:
                n = self.m_num_objects
                if c.getCellId() in self.m_bases:
                    n = self.m_num_base_objects
                for i in range(n):
                    obj = random.choice(self.m_objects)
                    obj = copy.copy(obj)
                    obj.setCellId(c.getCellId())
                    obj.setId("OBJ%05d" % (self.m_object_id))
                    c.addObject(obj)
                    self.m_object_id += 1

        return
    
    def finalize(self):
        if not self.m_finalized:
            self.linkCells()
            self.findCliffs()
            self.placeBases()
            self.placeGoal()
            self.placeObjects()
        self.m_finalized = True
        return

    def interfaceString(self):
        ice_string = ""
        if self.m_percent_ice > 0:
            ice_string = "Interface: ice        0     10           1       0\n"
        return """
#          title damage energy traversable is_fall
Interface: plain      0      0           1       0
Interface: rocks      1      0           1       0
Interface: mud        0      1           1       0
Interface: wall      10      1           0       0
Interface: cliff      0      0           1       1
""" + ice_string

    def __str__(self):
        self.finalize()
        s = self.interfaceString()
        for c in self.m_cells:
            if c:
                s += str(c) + "\n"
        for b in self.m_bases:
            s += "Base: %d\n" % (b)
        s += "Goal: %d\n" % (self.m_goal)
        return s
    
def main():
    print "this module has no test routine"
    return

if __name__ == "__main__":
    main()
