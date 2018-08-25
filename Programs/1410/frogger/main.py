import pygame
import game_mouse
import froggerlib


# Starter code for PyGame applications

class PygameStarter(game_mouse.Game):

    def __init__(self, width, height, fps):

        game_mouse.Game.__init__(self, "Pygame Starter",
                                 width,
                                 height,
                                 fps)
        self.frog = froggerlib.Frog(300,655,20,20,300,655,8,50,50)

        self.cars = [       # x, y, w, h, dx, dy
            froggerlib.Car(100, 550, 40, 30, -40 , 550, 8),
            froggerlib.Car(200, 550, 40, 30, -40 , 550, 8),
            froggerlib.Car(400, 550, 40, 30, -40 , 550, 8),
        ]
        self.racers = [
            froggerlib.RaceCar(0, 400, 40, 30, self.width , 400, 5, 10),
            froggerlib.RaceCar(0, 400, 40, 30, self.width , 400, 5, 10)

        ]
        self.dozers = [
            froggerlib.Dozer(100, 500, 40, 30, -40 , 500, 5),
            froggerlib.Dozer(300, 500, 40, 30, -40 , 500, 5),
            froggerlib.Dozer(500, 500, 40, 30, -40 , 500, 5)
        ]
        self.trucks = [
            froggerlib.Truck(50, 450, 80, 30, self.width , 450, 6),
            froggerlib.Truck(250, 450, 80, 30, self.width , 450, 6),
            froggerlib.Truck(400, 450, 80, 30, self.width , 450, 6)
        ]
        self.dodge = self.cars + self.racers + self.dozers + self.trucks

        self.alligators = [       # x,y,w,h,dx,dy,s
            froggerlib.Alligator(50, 150, 80, 30,self.width, 150, 6),
            froggerlib.Alligator(300, 150, 80, 30, self.width, 150, 6),
            froggerlib.Alligator(450, 150, 80, 30, self.width, 150, 6)
        ]

        self.turtles = [  # x,y,w,h,dx,dy,s
            froggerlib.Turtle(200, 200, 50, 30, self.width, 200, 3),
            froggerlib.Turtle(300, 200, 50, 30, self.width, 200, 3),
            froggerlib.Turtle(400, 200, 50, 30, self.width, 200, 3)
        ]

        self.logs = [  # x,y,w,h,dx,dy,s
            froggerlib.Log(100, 250, 100, 30, -80, 250, 5),
            froggerlib.Log(300, 250, 100, 30, -80, 250, 5),
            froggerlib.Log(500, 250, 100, 30, -80, 250, 5),
            froggerlib.Log(100, 100, 100, 30, -80, 100, 5),
            froggerlib.Log(300, 100, 100, 30, -80, 100, 5),
            froggerlib.Log(500, 100, 100, 30, -80, 100, 5)
        ]

        self.bases = self.logs + self.alligators + self.turtles

        self.stage1 = froggerlib.Stage(0, 295, self.width, 100)
        self.stage2 = froggerlib.Stage(0, 595, self.width, 100)
        self.road = froggerlib.Road(0, 395, self.width, 200)

        self.homes = [
            froggerlib.Home(50, 50, 50, 50),
            froggerlib.Home(150, 50, 50, 50),
            froggerlib.Home(250, 50, 50, 50),
            froggerlib.Home(350, 50, 50, 50),
            froggerlib.Home(450, 50, 50, 50),
            froggerlib.Home(550, 50, 50, 50),]

        self.water = froggerlib.Water(0, 100, self.width, 200)

        self.grass = [
            froggerlib.Grass(0, 50, 50, 50),
            froggerlib.Grass(100, 50, 50, 50),
            froggerlib.Grass(200, 50, 50, 50),
            froggerlib.Grass(300, 50, 50, 50),
            froggerlib.Grass(400, 50, 50, 50),
            froggerlib.Grass(500, 50, 50, 50),
        ]


    def restart(self):
        self.frog.setX(300)
        self.frog.setY(655)
        self.frog.setDesiredX(300)
        self.frog.setDesiredY(655)

    def game_over(self):
        if self.frog.outOfBounds(self.width, self.height):
            return True

        for base in self.bases:
            if base.supports(self.frog):
                print(self.frog)
                return False

        if self.water.hits(self.frog):
            print(self.frog)
            return True

        for grass in self.grass:
            if grass.hits(self.frog):
                return True

        for car in self.dodge:
            if car.hits(self.frog):
                return True

        for home in self.homes:
            if home.containsLocatable(self.frog):#####################
                return True

        return False

    def game_logic(self, keys, newkeys, buttons, newbuttons, mouse_position):
        x = mouse_position[0]
        y = mouse_position[1]

        if self.game_over():
            if pygame.K_r in newkeys:
                print('win')
                self.restart()
            else:
                if pygame.K_r in newkeys:
                    print('loser')
                    self.restart()
            return

        if pygame.K_UP in newkeys:
            self.frog.up()

        if pygame.K_DOWN in newkeys:
            self.frog.down()

        if pygame.K_LEFT in newkeys:
            self.frog.left()

        if pygame.K_RIGHT in newkeys:
            self.frog.right()

        self.frog.move()

        for car in self.dodge:
            car.move()
            if car.atDesiredLocation():
                if car.getX() > 55:
                    car.setX(0-car.getWidth())
                else:
                    car.setX(self.width)

        for base in self.bases:
            base.move()
            if base.atDesiredLocation():
                if base.getX() > 55:
                    base.setX(0-base.getWidth())
                else:
                    base.setX(self.width)



    def paint(self, surface):
        surface.fill((0,0,0))

        rect = pygame.Rect(self.stage1.getX(),
                           self.stage1.getY(),
                           self.stage1.getWidth(),
                           self.stage1.getHeight())
        pygame.draw.rect(surface, (144, 144, 144), rect)

        rect = pygame.Rect(self.stage2.getX(),
                           self.stage2.getY(),
                           self.stage2.getWidth(),
                           self.stage2.getHeight())
        pygame.draw.rect(surface, (144, 144, 144), rect)

        rect = pygame.Rect(self.road.getX(),
                           self.road.getY(),
                           self.road.getWidth(),
                           self.road.getHeight())
        pygame.draw.rect(surface, (55, 55, 55), rect)

        rect = pygame.Rect(self.water.getX(),
                         self.water.getY(),
                         self.water.getWidth(),
                         self.water.getHeight())
        pygame.draw.rect(surface, (0, 0, 255), rect)


        for car in self.cars:
            rect = pygame.Rect(car.getX(),
                           car.getY(),
                           car.getWidth(),
                           car.getHeight())
            pygame.draw.rect(surface, (255, 0, 0), rect)

        for racecar in self.racers:
            rect = pygame.Rect(racecar.getX(),
                               racecar.getY(),
                               racecar.getWidth(),
                               racecar.getHeight())
            pygame.draw.rect(surface, (220, 220, 220), rect)

        for dozer in self.dozers:
            rect = pygame.Rect(dozer.getX(),
                               dozer.getY(),
                               dozer.getWidth(),
                               dozer.getHeight())
            pygame.draw.rect(surface, (255, 255, 0), rect)

        for truck in self.trucks:
            rect = pygame.Rect(truck.getX(),
                               truck.getY(),
                               truck.getWidth(),
                               truck.getHeight())
            pygame.draw.rect(surface, (160, 0, 160), rect)

        for grass in self.grass:
            rect = pygame.Rect(grass.getX(),
                               grass.getY(),
                               grass.getWidth(),
                               grass.getHeight())
            pygame.draw.rect(surface, (0, 150, 0), rect)

        for home in self.homes:
            rect = pygame.Rect(home.getX(),
                               home.getY(),
                               home.getWidth(),
                               home.getHeight())
            pygame.draw.rect(surface, (165, 42, 42), rect)

        for log in self.logs:
            rect = pygame.Rect(log.getX(),
                               log.getY(),
                               log.getWidth(),
                               log.getHeight())
            pygame.draw.rect(surface, (200, 200, 200),rect)

        for turtle in self.turtles:
            rect = pygame.Rect(turtle.getX(),
                               turtle.getY(),
                               turtle.getWidth(),
                               turtle.getHeight())
            pygame.draw.rect(surface, (200, 200, 200),rect)

        for alligator in self.alligators:
            rect = pygame.Rect(alligator.getX(),
                               alligator.getY(),
                               alligator.getWidth(),
                               alligator.getHeight())
            pygame.draw.rect(surface, (200, 200, 200),rect)

        rect = pygame.Rect(self.frog.getX(),
                           self.frog.getY(),
                           self.frog.getWidth(),
                           self.frog.getHeight())
        pygame.draw.rect(surface, (0, 255, 0), rect)
        return

def main():
    screen_width = 600
    screen_height = 700
    frames_per_second = 30
    game = PygameStarter(screen_width, screen_height, frames_per_second)
    game.main_loop()
    return
    
if __name__ == "__main__":
    main()