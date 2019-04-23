import sys
from pygame.locals import *
from Classes import *


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
J1_TIP = (JOINT_LEN / 2, 0)
RESET_J1_TIP = J1_TIP
J1_ANGLE = -90

"""Second joint related variables"""
J2_COORD = (J1_TIP[0] + J1_COORD[0], J1_TIP[1] + J1_COORD[1])
J2_TIP = (J1_TIP[0], J1_TIP[1])
RESET_J2_TIP = J2_TIP
J2_ANGLE = 0

"""Third joint related variables"""
J3_COORD = (J2_TIP[0] + J2_COORD[0], J2_TIP[1] + J2_COORD[1])
J3_TIP = (J1_TIP[0], J1_TIP[1])
RESET_J3_TIP = J3_TIP
J3_ANGLE = 0

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
flag = 1


def controls(left: bool, right: bool):
    global J1_ANGLE
    global J1_TIP
    if left and J1_ANGLE > -180:
        J1_TIP = S
        J1_ANGLE += 3
        J1_TIP = rotate(J1_TIP, J1_ANGLE)
    if right:
        J1_TIP = S
        J1_ANGLE -= 3
        J1_TIP = rotate(J1_TIP, J1_ANGLE)



def draw_lines():
    pg.draw.line(window, WHITE, J1_COORD,
                 (J1_TIP[0] + J1_COORD[0], J1_TIP[1] + J1_COORD[1]), JOINT_WIDTH)

    """Second joint movement"""
    global J2_COORD
    J2_COORD = (J1_TIP[0] + J1_COORD[0], J1_TIP[1] + J1_COORD[1])
    global J2_TIP
    J2_TIP = rotate(J2_TIP, 14)
    pg.draw.line(window, SOME_COLOR, J2_COORD,
                 (J2_TIP[0] + J1_TIP[0] + J1_COORD[0], J2_TIP[1] + J1_TIP[1] + J1_COORD[1]), JOINT_WIDTH)

    """Third joint movement"""
    global J3_COORD
    J3_COORD = (J2_TIP[0] + J1_COORD[0] + J1_TIP[0], J2_TIP[1] + J1_COORD[1] + J1_TIP[1])
    global J3_TIP
    J3_TIP = rotate(J3_TIP, 16)
    pg.draw.line(window, SOME_COLOR, J3_COORD,
                 (J3_TIP[0] + J2_TIP[0] + J2_COORD[0],
                  J3_TIP[1] + J2_TIP[1] + J2_COORD[1]), JOINT_WIDTH)





def main():
    robot = RobotArm(window)
    left_1 = False
    right_1 = False
    flag = 1
    while True:
        pg.time.Clock().tick(30)
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
                if keys[K_KP1]:
                    left_1 = True
                if keys[K_KP3]:
                    right_1 = True
            if event.type == KEYUP:
                if event.key == K_KP1:
                    left_1 = False
                if event.key == K_KP3:
                    right_1 = False
        print(-J1_ANGLE)
        controls(left_1, right_1)

        #J1_ANGLE = 180
        if flag:
            window.fill(BLACK)
            BASE.fill(WHITE)
            window.blit(BASE, BASE_COORD)

            robot.rotate_j1()
            robot.draw_joints()

            pg.display.flip()
            #flag = 0
            #pg.time.delay(40)
##Main loops ends here

main()