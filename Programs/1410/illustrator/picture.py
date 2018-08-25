import pygame
import circle
import square
import elipse
import poly
import wick
class Picture:
    def __init__( self, width, height ):
        self.mWidth = width
        self.mHeight = height
        self.mSquare = square.Square(0, 0, self.mWidth, self.mHeight, (0, 0, 0))
        self.mSquare2 = square.Square(300, 300, 40, 40, (250, 125, 20))
        self.mSquare3 = square.Square(380, 300, 40, 40, (250, 125, 20))
        self.mSquare4 = square.Square(460, 300, 40, 40, (250, 125, 20))
        self.mSquare5 = square.Square(260, 300, 40, 40, (250, 125, 20))
        self.mSquare6 = square.Square(180, 300, 40, 40, (250, 125, 20))
        self.mSquare7 = square.Square(100, 300, 40, 40, (250, 125, 20))
        self.mSquare8 = square.Square(280, 400, 40, 20, (125, 125, 125))
        self.mCircle = circle.Circle( 300, 380, 10, ( 245, 205, 29 ) )
        self.mCircle2 = circle.Circle(300, 370, 20, (255, 0, 0))
        self.mElipse1 = elipse.Elipse( 25, 25, 550, 450, ( 250, 125, 20 ) )
        self.mElipse2 = elipse.Elipse( 75, 125, 450, 300, ( 0, 0, 0 ) )
        points1 = [ ( 200, 200 ), ( 235, 235 ), ( 235, 225 ), ( 210, 200 ), ( 235, 175 ), ( 235, 165 ), ( 200, 200 ) ]
        points2 = [ ( 365, 200 ), ( 400, 235 ), ( 400, 225 ), ( 375, 200 ), ( 400, 175 ), ( 400, 165 ), ( 365, 200 ) ]
        points3 = [(120, 100), (50, 300), (550, 300), (500, 100)]
        points4 = [(300, 220), (250, 280), (350, 280), (300, 220)]
        self.mPoly1 = poly.Poly( points1, ( 0, 0, 0 ) )
        self.mPoly2 = poly.Poly( points2, ( 0, 0, 0 ) )
        self.mPoly3 = poly.Poly(points3, (250, 125, 20))
        self.mPoly4 = poly.Poly(points4, (0, 0, 0))
        self.mWick = wick.Wick( 300, 390, 0, 20, ( 255, 255, 255 ) )

    def draw( self, surface ):
        self.mSquare.draw( surface )
        self.mElipse1.draw(surface)
        self.mElipse2.draw( surface )
        self.mPoly3.draw(surface)
        self.mPoly1.draw(surface)
        self.mPoly2.draw(surface)
        self.mPoly4.draw(surface)
        self.mWick.draw(surface)
        self.mCircle2.draw(surface)
        self.mCircle.draw(surface)
        self.mSquare2.draw(surface)
        self.mSquare3.draw(surface)
        self.mSquare4.draw(surface)
        self.mSquare5.draw(surface)
        self.mSquare6.draw(surface)
        self.mSquare7.draw(surface)
        self.mSquare8.draw(surface)