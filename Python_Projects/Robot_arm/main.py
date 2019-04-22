import pygame as pg
import math
import sys
from pygame.locals import *


MAIN_WIN = (1080, 720)

"""Coordinates and Surface of the bases"""
BASE_SURFACE = (240, 30)
BASE_COORD = (1080 / 2 - 1080 / 8, 720 - 720 / 5)
BASE = pg.Surface(BASE_SURFACE)

"""Joint related variables"""
JOINT_LEN = 120
JOINT_WIDTH = 5

"""First joint related variables"""
J1_COORD = (1080 / 2, BASE_COORD[1])
J1_TIP = (JOINT_LEN, 0)

"""Second joint related variables"""
J2_COORD = (J1_TIP[0] + J1_COORD[0], J1_TIP[1] + J1_COORD[1])
J2_TIP = (J1_TIP[0], J1_TIP[1])

"""Third joint related variables"""
J3_COORD = (J2_TIP[0] + J2_COORD[0], J2_TIP[1] + J2_COORD[1])
J3_TIP = (J1_TIP[0], J1_TIP[1])

"""Some colors for clarity"""
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
SOME_COLOR = (221, 21, 43)
MORE_COLOR = (35, 127, 32)


def rotate(coord: tuple, deg_angle: int) -> float:
    x = (((coord[0]) * math.cos(math.radians(deg_angle))
         - (coord[1]) * math.sin(math.radians(deg_angle))))
    y = (((coord[0]) * math.sin(math.radians(deg_angle))
          + (coord[1]) * math.cos(math.radians(deg_angle))))
    return x, y


pg.init()
window = pg.display.set_mode(MAIN_WIN, RESIZABLE)
print(MAIN_WIN)
flag = 1
"""Main loops starts here"""
while True:
    for event in pg.event.get():
        keys = pg.key.get_pressed()
        if event.type == QUIT:
            pg.quit()
            sys.exit(0)
        if event.type == KEYDOWN:
            """Quit the program"""
            if keys[K_LMETA] and keys[K_q]:
                pg.quit()
                sys.exit(0)
            if keys[K_ESCAPE]:
                pg.quit()
                sys.exit(0)

            """Pause the program"""
            if keys[K_SPACE]:
                if flag == 0:
                    flag = 1
                else:
                    flag = 0

    if flag:
        window.fill(BLACK)
        BASE.fill(WHITE)
        window.blit(BASE, BASE_COORD)

        """First joint movement"""
        J1_TIP = rotate(J1_TIP, 12)
        pg.draw.line(window, WHITE, J1_COORD,
                     (J1_TIP[0] + J1_COORD[0], J1_TIP[1] + J1_COORD[1]), JOINT_WIDTH)

        """Second joint movement"""
        J2_COORD = (J1_TIP[0] + J1_COORD[0], J1_TIP[1] + J1_COORD[1])
        J2_TIP = rotate(J2_TIP, 14)
        pg.draw.line(window, SOME_COLOR, J2_COORD,
                     (J2_TIP[0] + J1_TIP[0] + J1_COORD[0], J2_TIP[1] + J1_TIP[1] + J1_COORD[1]), JOINT_WIDTH)

        """Third joint movement"""
        J3_COORD = (J2_TIP[0] + J1_COORD[0] + J1_TIP[0], J2_TIP[1] + J1_COORD[1] + J1_TIP[1])
        J3_TIP = rotate(J3_TIP, 16)
        pg.draw.line(window, SOME_COLOR, J3_COORD,
                     (J3_TIP[0] + J2_TIP[0] + J2_COORD[0],
                      J3_TIP[1] + J2_TIP[1] + J2_COORD[1]), JOINT_WIDTH)

        pg.display.flip()
        pg.time.delay(40)
##Main loops ends here