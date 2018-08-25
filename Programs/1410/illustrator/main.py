import pygame
import math
import game_mouse
import picture
class PygameApp(game_mouse.Game):
    def __init__(self, width, height, frame_rate):

        # Provide the title of the app in the window's bar
        game_mouse.Game.__init__(self, "Sunset",
                                 width,
                                 height,
                                 frame_rate)
        # Create any app data
        self.mPicture = picture.Picture(width, height)

    def game_logic(self, keys, newkeys, buttons, newbuttons, mouse_position):
        x = mouse_position[0]
        y = mouse_position[1]

        if pygame.K_a in newkeys:
            print("a key pressed")

        if 1 in newbuttons:
            print("button clicked")

    def paint(self, surface):
        # draw the window
        self.mPicture.draw(surface)

def main():
    pygame.font.init()
    game = PygameApp(600, 500, 10)
    game.main_loop()

if __name__ == "__main__":
    main()