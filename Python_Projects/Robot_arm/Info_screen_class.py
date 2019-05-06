import pygame as pg
import operator
import robot_arm_class
from G_Var import *
import numpy as np


class InfoScreen:
    title_font_size = 30
    info_font_size = 20

    def __init__(self, window):
        self.window = window

        self.font_big = pg.font.SysFont(None, self.title_font_size)
        self.font_small = pg.font.SysFont(None, self.info_font_size)

        self.screen_surface = (WIN_WIDTH / 8, WIN_HEIGHT / 3)
        self.frame = pg.Surface(self.screen_surface)

        self.text_title = self.font_big.render("Info", True, BLUE)
        self.info_list = {}

    # Calculate the center of mass of the 3 joints (first version does not take in account neither servos nor base)
    @staticmethod
    def get_center_of_mass(robot: robot_arm_class.RobotArm):
        center = np.add(robot.first_joint_tip * 3, np.add(robot.second_joint_tip * 2, robot.third_joint_tip))
        # center = np.add()
        # center_y = (robot.first_joint_tip[1] + robot.second_joint_tip[1] + robot.third_joint_tip[1]) / 3
        # print(robot.base_coord)
        # print(np.dot([1, -1], robot.base_coord))
        return int(center[0] + robot.base_coord[0]), int(robot.base_coord[1] - center[1])

    # Centering pycharm_obj given width value
    @staticmethod
    def obj_center_x(obj_width, width):
        return (width / 2) - obj_width / 2

    def print_info(self, robot: robot_arm_class.RobotArm):

        # Starting point for printing informations
        text_x = 15
        text_y = 40
        # print(robot.first_joint_tip * 2)
        # All three joint6's angles
        self.info_list['first joint angle : '] = str(robot.first_joint_angle)
        self.info_list['second joint angle : '] = str(robot.second_joint_angle)
        self.info_list['third joint angle : '] = str(robot.third_joint_angle)

        # This ugly line just adds together the 3 vectors representing the robot arm joints
        # tip = tuple(map(operator.add, robot.first_joint_tip,
        #                 tuple(map(operator.add, robot.second_joint_tip, robot.third_joint_tip))))

        tip = np.add(robot.first_joint_tip, np.add(robot.second_joint_tip, robot.third_joint_tip))
        # This ugly line first convert the tip of the arm from float to integer than from integer to string
        # And finally formats the line with brackets
        self.info_list['tip coordinates : '] = np.array2string(tip.astype(int), separator=', ')

        # Iterate through dict and print both index (= key) and value (= val)
        for key, val in self.info_list.items():
            # Prints the index name
            self.frame.blit(self.font_small.render(key, True, RED), (text_x, text_y))

            # Shifts X coordinates right of length value and length of " "
            text_x += self.font_small.size(key)[0]
            text_x += self.font_small.size(" ")[0]

            # Prints the value
            self.frame.blit(self.font_small.render(val, True, RED), (text_x, text_y))

            # Go to the next line
            text_y += self.info_font_size * 1.5
            text_x = 15

    def print_to_screen(self, robot: robot_arm_class.RobotArm):
        # Reset frame
        self.frame.fill(BLACK)

        # Draw the frame
        pg.draw.rect(self.frame, BLUE, (0, 0, self.screen_surface[0], self.screen_surface[1]), 10)

        # Print informations
        self.print_info(robot)

        # Draw the center of mass of the structure
        pg.draw.circle(self.window, RED, self.get_center_of_mass(robot), 5)

        # Blit everything
        self.frame.blit(self.text_title, (self.obj_center_x(self.font_big.size("Info")[0], self.screen_surface[0]), 12))
        self.window.blit(self.frame, (WIN_WIDTH - self.screen_surface[0] - 5, 5))
