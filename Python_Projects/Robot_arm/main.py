import tools
import math
from G_Var import *
import pygame as pg
import Classes


def rotate(coord: tuple, deg_angle: int) -> float:
    x = (((coord[0]) * math.cos(math.radians(deg_angle))
         - (coord[1]) * math.sin(math.radians(deg_angle))))
    y = (((coord[0]) * math.sin(math.radians(deg_angle))
          + (coord[1]) * math.cos(math.radians(deg_angle))))
    return x, y


pg.init()
window = pg.display.set_mode(MAIN_WIN, pg.RESIZABLE)


def main():
    flag = 1
    robot = Classes.RobotArm(window)
    left_1 = False
    right_1 = False
    flag = 1
    x = 1
    y = 2
    print(robot.first_joint_tip, robot.second_joint_tip)
    while True:
        pg.time.Clock().tick(60)
        # flag = tools.event_loop(flag, robot)
        keys = pg.key.get_pressed()
        for event in pg.event.get():
            tools.quit_program(event, keys)
            if keys[pg.K_SPACE]:
                if flag == 0:
                    flag = 1
                else:
                    flag = 0
            robot.get_controls(keys, event)
        if flag:
            window.fill(tools.BLACK)
            # if robot.first_joint_angle <= 46 and x == -1:
            #     x = 1
            # if robot.first_joint_angle >= 134:
            #     x = -1
            # if robot.second_joint_angle == 46 and y == -2:
            #     y = 2
            # if robot.second_joint_angle == 134:
            #     y = -2
            # robot.rotate_j2(y)
            # print(robot.second_joint_angle)
            # robot.rotate_j1(x)
            robot.move_arm()
            robot.draw_joints()
            pg.display.flip()


main()
