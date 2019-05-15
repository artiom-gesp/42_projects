import tools
import sys
from settings import *
import pygame as pg
import robot_arm_class
import info_screen_class

pg.init()
pg.font.init()

print(MAIN_WIN[0], MAIN_WIN[1])
if not (1980 >= MAIN_WIN[0] >= 1280 >= MAIN_WIN[1] >= 720):
    sys.exit("Wrong window size")

window = pg.display.set_mode(MAIN_WIN)


def main():
    flag = True
    # Generate the arm
    robot = robot_arm_class.RobotArm(window)
    info_screen = info_screen_class.InfoScreen(window)
    x, y = 0, 0
    while True:
        # pg.time.Clock().tick(60)
        keys = pg.key.get_pressed()
        for event in pg.event.get():
            # Checks if event : ESC, CMD + Q or QUIT are triggered
            tools.quit_program(event, keys)
            # Makes a break and prevent any further move
            if keys[pg.K_SPACE]:
                if not flag:
                    flag = True
                else:
                    flag = False
            if event.type == pg.MOUSEBUTTONDOWN:
                robot.x_line, robot.y_line = pg.mouse.get_pos()
            # Get joints movement related events
            robot.get_controls(event)
        if flag:
            # Reset background
            window.fill(tools.BLACK)

            # Rotate joints
            robot.move_arm()

            robot.draw_line()

            # Draw joints
            robot.draw_joints()

            # Draw informations
            info_screen.print_to_screen(robot)

            # Reset display
            pg.display.flip()


main()
