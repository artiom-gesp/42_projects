import sys
from Classes import *
from pygame.locals import *


def quit_program(event, keys):
    if keys[K_LMETA] and keys[K_q]:
        pg.quit()
        sys.exit(0)
    if keys[K_ESCAPE]:
        pg.quit()
        sys.exit(0)
    if event.type == QUIT:
        pg.quit()
        sys.exit(0)
