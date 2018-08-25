from circle import Circle
class Bullet(Circle):
    def __init__(self,x,y,dx,dy,rotation,world_width,world_height):
        radius = 3
        Circle.__init__(self,x,y,dx,dy,rotation,radius,world_width,world_height)
        self.mAge = 0
        self.accelerate(100.0)
        self.move(0.1)

    def getAge(self):
        return self.mAge

    def setAge(self,age):
        self.mAge = age

    def evolve(self,dt):
        self.move(dt)
        age = self.getAge() + dt
        self.mAge += dt
        if age >= 6:
            self.setActive(False)
