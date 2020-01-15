import pygame
import math
import game_mouse
import world_data as data
import inputbox

M_DISPLAY = 1
M_GET_Z   = 2

class WorldEditor(game_mouse.Game):

    def __init__(self, width, height, frames_per_second):
        #
        # get world information, and calculate adjusted width and height
        #
        self.data = data.WorldData()
        (self.min_x, self.max_x) = self.data.getXRange()
        (self.min_y, self.max_y) = self.data.getYRange()
        (self.min_z, self.max_z) = self.data.getZRange()
        self.cells_wide = int((self.max_x - self.min_x) / 1000.0) + 1
        self.cells_high =int ((self.max_y - self.min_y) / 1000.0) + 1
        dx  = int(width / self.cells_wide)
        dy  = int(height / self.cells_high)
        if dx < dy:
            self.cell_size = dx
        else:
            self.cell_size = dy
        self.delta_z = self.max_z - self.min_z

        width  = self.cells_wide * self.cell_size
        height = self.cells_high * self.cell_size

        self.current_cell_id = None

       
        #
        # Now, initialize pygame
        #
        game_mouse.Game.__init__(self, "Scavenger Editor",
                                 width,
                                 height,
                                 frames_per_second)
        
        pygame.mouse.set_visible(True)
        self.font = pygame.font.SysFont(None, 12)

        # some colors
        self.interface_colors = [ (255, 0, 0, ), # ERROR
                                  (int(.1*255), int(.6*255), int(.1*255)), # PLAIN
                                  (int(.1*255), int(.4*255), int(.4*255)), # ROCKS
                                  (int(.4*255), int(.2*255), int(.1*255)), # MUD
                                  (int(.9*255), int(.9*255), int(.9*255)), # ICE
                                  (int(.1*255), int(.1*255), int(.1*255)), # WALL
                                  (int(.5*255), int(.5*255), int(.1*255)), # CLIFF
                                  ]
        self.text_color = (0,0,0)
        
        self.createCellMap()

        self.mode = M_DISPLAY
                
        return

    def cellIndex(self, x, y):
        return self.width*y + x

    def createCellMap(self):
        self.cell_map = {}
        for cell in self.data.getCells().itervalues():
            dx = int((cell.x - self.min_x)/1000.0)
            dy = int((cell.y - self.min_y)/1000.0)
            self.cell_map[self.cellIndex(dx, dy)] = cell.id
        return

    def clickCell(self, x, y):
        x1 = x/self.cell_size
        y1 = (self.height-y)/self.cell_size
        i = self.cellIndex(x1, y1)
        if self.cell_map.has_key(i):
            self.current_cell_id = self.cell_map[i]
        return
    
    def game_logic(self, keys, newkeys, buttons, newbuttons, mouse_position):
        x = mouse_position[0]
        y = mouse_position[1]
        if not self.current_cell_id:
            if 1 in newbuttons:
                self.clickCell(x, y)
        else:
            if 1 in newbuttons:
                self.current_cell_id = None
            elif pygame.K_z in newkeys:
                self.mode = M_GET_Z

        if (pygame.K_s in newkeys) and ((pygame.K_LCTRL in keys) or (pygame.K_RCTRL in keys)):
            self.data.writeFile("world_new.txt")
            print "Saved"

        return


    def drawTextLeft(self, text, surface, x, y):
        textobj = self.font.render(text, 1, self.text_color)
        textrect = textobj.get_rect()
        textrect.topleft = (x, y)
        surface.blit(textobj, textrect)
        return
    
    def drawTextCenter(self, text, surface, x, y):
        textobj = self.font.render(text, 1, self.text_color)
        textrect = textobj.get_rect()
        textrect.center = (x, y)
        surface.blit(textobj, textrect)
        return

    def cellColor(self, cell):
        dz = (cell.z - self.min_z)/self.delta_z
        r = min(max(int((1.0-dz) * 255), 0), 255)
        g = min(max(int((1.0-dz) * 255), 0), 255)
        b = min(max(int(dz * 255), 0), 255)
        color = (r, g, b)
        return color

    def cellPixels(self, cell):
        dx = (cell.x - self.min_x)/1000.0
        dy = (cell.y - self.min_y)/1000.0
        x = int(self.cell_size * dx)
        y = self.height - int(self.cell_size * (dy+1))
        w = self.cell_size
        h = self.cell_size
        return x, y, w, h

    def drawCellInterfaces(self, surface, cell, x, y, w, h, t):
        xl = x
        xr = x+w-1
        yt = y
        yb = y+h-1
        
        points = []
        points.append( [ (xl,yt), (xr, yt), (xr-t, yt+t), (xl+t, yt+t) ] )  # N
        points.append( [ (xl,yb), (xr, yb), (xr-t, yb-t), (xl+t, yb-t) ] )  # S
        points.append( [ (xr,yt), (xr, yb), (xr-t, yb-t), (xr-t, yt+t) ] )  # E
        points.append( [ (xl,yt), (xl, yb), (xl+t, yb-t), (xl+t, yt+t) ] )  # W
        
        for i in range(4):
            pygame.draw.polygon(surface, self.interface_colors[cell.interfaces[i]], points[i])
        
        return
    
    def drawCell(self, surface, cell):
        x, y, w, h = self.cellPixels(cell)
        r = pygame.Rect(x, y, w, h)
        pygame.draw.rect(surface, self.cellColor(cell), r)
        self.drawCellInterfaces(surface, cell, x, y, w, h, 1)
        
        self.drawTextLeft("%d" % (len(cell.objects)), surface, x+w/5, y+h/5)
        return

    def drawObject(self, surface, obj):
        return
    
    def drawBase(self, surface, base):
        cell = self.data.getCell(base.cell_id)
        x, y, w, h = self.cellPixels(cell)
        x0 = (x+x+w)/2
        y0 = (y+y+h)/2
        pygame.draw.circle(surface, (0, 0, 0), (x0, y0), w/4)
        return
    
    def drawGoal(self, surface, goal):
        cell = self.data.getCell(goal.cell_id)
        x, y, w, h = self.cellPixels(cell)
        x0 = (x+x+w)/2
        y0 = (y+y+h)/2
        pygame.draw.circle(surface, (200, 0, 0), (x0, y0), w/4)
        return
    
    def drawCells(self, surface):
        for c in self.data.getCells().itervalues():
            self.drawCell(surface, c)
        return

    def drawObjects(self, surface):
        for o in self.data.getObjects().itervalues():
            self.drawObject(surface, o)
        return

    def drawBases(self, surface):
        for b in self.data.getBases():
            self.drawBase(surface, b)
        return

    def drawGoals(self, surface):
        for g in self.data.getGoals():
            self.drawGoal(surface, g)
        return


    def drawCellBig(self, surface, cell):
        x, y, w, h = (0, 0, self.width, self.height)
        r = pygame.Rect(x, y, w, h)
        pygame.draw.rect(surface, self.cellColor(cell), r)
        self.drawCellInterfaces(surface, cell, x, y, w, h, 10)
        return
    
    def drawCellDisplay(self, surface):
        cell = self.data.getCells()[self.current_cell_id]
        self.drawCellBig(surface, cell)
        x = self.width/10
        y = self.height/10
        dy = 18 
        self.drawTextLeft("X: %7.0f" % (cell.x), surface, x, y)
        y += dy
        self.drawTextLeft("Y: %7.0f" % (cell.y), surface, x, y)
        y += dy
        self.drawTextLeft("Z: %7.0f" % (cell.z), surface, x, y)
        y += dy
        y += dy
        
        #
        for object_id in cell.objects:
            obj = self.data.getObject(object_id)
            self.drawTextLeft(str(obj), surface, x, y)
            y += dy
        y += dy

        #
        for base_id in cell.bases:
            base = self.data.getBase(base_id)
            self.drawTextLeft(str(base), surface, x, y)
            y += dy
        y += dy
        #
        for goal_id in cell.goals:
            goal = self.data.getGoal(goal_id)
            self.drawTextLeft(str(goal), surface, x, y)
            y += dy
        y += dy
        
        return
    
    def paint(self, surface):
        pygame.draw.rect(surface, (0,0,0), pygame.Rect(0, 0, self.width, self.height))
        if self.mode == M_DISPLAY:
            if self.current_cell_id:
                self.drawCellDisplay(surface)
            else:
                self.drawCells(surface)
                self.drawObjects(surface)
                self.drawBases(surface)
                self.drawGoals(surface)
        elif self.mode == M_GET_Z:
            z = float(inputbox.ask(surface, "Elevation? "))
            self.data.getCells()[self.current_cell_id].z = z
            self.mode = M_DISPLAY
            
        return

def main():
    pygame.font.init()
    p = WorldEditor(700, 700, 5)
    p.main_loop()
    
if __name__ == "__main__":
    main()

