import sys
from robot_arm_class import *
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


def add_vectors(*vectors) -> tuple:
    vec_sum: tuple = (0, 0)
    for vector in vectors:
        vec_sum = tuple(map(operator.add, sum, vector))
    return vec_sum
