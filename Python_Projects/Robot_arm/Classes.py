import pygame as pg
import math
from G_Var import *
import operator


class RobotArm:
    def __init__(self, window):
        base_surface = (240, 30)
        self.base_coord = (1080 / 2 - 1080 / 8, 720 - 720 / 5)
        self.robot_base = pg.Surface(base_surface)

        self.joint_len = 120
        self.joint_width = 5

        self.first_joint_base = (0, 0)
        self.first_joint_angle = 45
        self.first_joint_tip = (120, 120)
        self.first_joint_plane_coord =\
            tuple(map(operator.add, self.first_joint_tip, self.base_coord))

        self.second_joint_base = self.first_joint_tip
        self.second_joint_angle = 45
        self.second_joint_tip = (120, 120)

        self.window = window

    @staticmethod
    def rotate(coord: tuple, deg_angle: int):
        x = ((coord[0]) * math.cos(math.radians(-deg_angle))
             - (coord[1]) * math.sin(math.radians(-deg_angle)))
        y = ((coord[0]) * math.sin(math.radians(-deg_angle))
             + (coord[1]) * math.cos(math.radians(-deg_angle)))
        return x, y

    def rotate_j1(self, angle: int = 1):
        self.first_joint_angle += angle
        self.first_joint_tip = self.rotate(self.first_joint_tip, self.first_joint_angle)

    def rotate_j2(self, angle: int = 1):
        self.second_joint_angle += angle
        self.second_joint_tip = self.rotate(self.first_joint_tip, self.first_joint_angle)

    def draw_joints(self):
        pg.draw.line(self.window, WHITE, self.base_coord, self.first_joint_plane_coord,
                     self.joint_width)
