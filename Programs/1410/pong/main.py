#
# Draw picture
#

import pygame
import math
import game_mouse
import pong

class PygameApp(game_mouse.Game):

    def __init__( self, width, height, frame_rate ):

        # title of the application is ""
        game_mouse.Game.__init__( self, "Pong",
                                  width,
                                  height,
                                  frame_rate )
        # create a Picture instance
        self.mPong = pong.Pong( width, height )
        return
        
        
    def game_logic( self, keys, newkeys, buttons, newbuttons, mouse_position ):
        x = mouse_position[0]
        y = mouse_position[1]

        if pygame.K_a in newkeys:
            print("a key pressed")
        
        if 1 in newbuttons:
            print("button clicked")

        self.mPong.update( 1 / self.frames_per_second, keys )

        return
    
    def paint( self, surface ):
        # draw the picture
        self.mPong.draw( surface )
        return

def main():
    pygame.font.init( )
    game = PygameApp( 800, 600, 30 )
    game.main_loop( )
    
if __name__ == "__main__":
    main()

