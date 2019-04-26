import pygame as pg
import math
from G_Var import *
import operator


class RobotArm:
    def __init__(self, window):
        # screen coordinates ((0, 0) is the base's cartesian coordinates
        self.base_coord = (WIN_WIDTH / 2, WIN_HEIGHT - WIN_HEIGHT / 5)

        # Arm base is represented by a rectangle
        self.base_surface = (int(WIN_WIDTH / 4.5), int(WIN_HEIGHT / 24))

        # create the surface representing the base
        self.robot_base = pg.Surface(self.base_surface)

        # characteristics proper to all joints
        self.joint_len = int(math.sqrt(math.pow(self.base_surface[0] / 2 + self.base_surface[1] / 2, 2)))
        self.joint_width = int(self.joint_len / 20)

        # cartesian coordinates of joint_1
        self.first_joint_base = (0, 0)
        # angle is relative to previous joint, for J1 its the base
        self.first_joint_tip = (-1 * self.joint_len, self.joint_len)
        print(self.first_joint_tip)
        self.first_joint_angle = 135

        # screen coordinates of joint_1
        self.first_joint_plane_coord = (self.first_joint_tip[0] + self.base_coord[0],
                                        (math.fabs(self.first_joint_tip[1] - self.base_coord[1])))
        # base of joint_2
        self.second_joint_base = self.first_joint_tip

        # angle between joint_1 and joint_2
        self.second_joint_angle = 90
        # cartesian coordinates of joint_2
        self.second_joint_tip = (-1 * self.first_joint_tip[0], self.first_joint_tip[1])
        # screen coordinates of joint_2
        self.second_plane_coord =\
            tuple(map(operator.add, self.first_joint_plane_coord, self.second_joint_base))

        # base of joint_3
        self.third_joint_base = self.second_joint_tip

        # angle between joint_2 and joint_3
        self.third_joint_angle = 90
        # cartesian coordinates of joint_3
        self.third_joint_tip = (-1 * self.first_joint_tip[0], -1 * self.first_joint_tip[1])
        # screen coordinates of joint_3
        self.third_plane_coord = \
            tuple(map(operator.add, self.first_joint_plane_coord, self.third_joint_base))

        # Set of variables to enable manual rotation
        self.left_j1 = False
        self.left_j2 = False
        self.right_j1 = False
        self.right_j2 = False
        self.left_j3 = False
        self.right_j3 = False

        # main window
        self.window = window

    # do a simple rotation in space using a rotation matrix
    @staticmethod
    def rotate(coord: tuple, deg_angle: int):
        x = ((coord[0]) * math.cos(math.radians(deg_angle))
             - (coord[1]) * math.sin(math.radians(deg_angle)))
        y = ((coord[0]) * math.sin(math.radians(deg_angle))
             + (coord[1]) * math.cos(math.radians(deg_angle)))
        return x, y

    # rotating joint_1 and adapt joint_2 to keep the same angle between them
    def rotate_j1(self, angle: int = 1):
        if (angle > 0 and self.first_joint_angle + angle < 140)\
                or (angle < 0 and 40 < self.first_joint_angle + angle):
            self.first_joint_angle += angle
            self.first_joint_tip = self.rotate(self.first_joint_tip, angle)
            self.second_joint_tip = self.rotate(self.second_joint_tip, angle)
            self.third_joint_tip = self.rotate(self.third_joint_tip, angle)

    # rotating joint_2
    def rotate_j2(self, angle: int = 1):
        if (angle > 0 and self.second_joint_angle + angle < 140)\
                or (angle < 0 and 40 < self.second_joint_angle + angle):
            self.second_joint_angle += angle
            self.second_joint_tip = self.rotate(self.second_joint_tip, angle)
            self.third_joint_tip = self.rotate(self.third_joint_tip, angle)

    # rotating joint_3
    def rotate_j3(self, angle: int = 1):
        if (angle > 0 and self.third_joint_angle + angle < 140)\
                or (angle < 0 and 40 < self.third_joint_angle + angle):
            self.third_joint_angle += angle
            self.third_joint_tip = self.rotate(self.third_joint_tip, angle)

    def draw_joints(self):
        self.robot_base.fill(WHITE)
        # base_coord being the origin, base_coord - base_surface is the top left corner of the base
        self.window.blit(self.robot_base, (self.base_coord[0] - self.base_surface[0] / 2, self.base_coord[1]))

        # Transposing a cartesian coordinates plane into a computer graphics plane
        self.first_joint_plane_coord = (self.first_joint_tip[0] + self.base_coord[0],
                                        (math.fabs(self.first_joint_tip[1] - self.base_coord[1])))

        # Drawing first joint
        pg.draw.line(self.window, WHITE, self.base_coord, self.first_joint_plane_coord,
                     self.joint_width)

        # Adjusting joint_2 coordinates
        self.second_joint_base = self.first_joint_plane_coord
        self.second_plane_coord = (self.second_joint_tip[0] + self.first_joint_plane_coord[0],
                                   (math.fabs(self.second_joint_tip[1]
                                              - self.first_joint_plane_coord[1])))

        # Drawing second joint
        pg.draw.line(self.window, WHITE, self.second_joint_base, self.second_plane_coord,
                     self.joint_width)

        # Adjusting joint_3 coordinates
        self.third_joint_base = self.second_plane_coord
        self.third_plane_coord = (self.third_joint_tip[0] + self.second_plane_coord[0],
                                  math.fabs(self.third_joint_tip[1]
                                            - self.second_plane_coord[1]))

        # Drawing third joint
        pg.draw.line(self.window, WHITE, self.third_joint_base, self.third_plane_coord,
                     self.joint_width)

    # While a key is maintained, keep sending a signal to move the associated joint
    def get_controls(self, event):
        if event.type == pg.KEYDOWN:
            if event.key == pg.K_KP1:
                self.left_j1 = True
            if event.key == pg.K_KP3:
                self.right_j1 = True
            if event.key == pg.K_KP4:
                self.left_j2 = True
            if event.key == pg.K_KP6:
                self.right_j2 = True
            if event.key == pg.K_KP7:
                self.left_j3 = True
            if event.key == pg.K_KP9:
                self.right_j3 = True
        if event.type == pg.KEYUP:
            if event.key == pg.K_KP1:
                self.left_j1 = False
            if event.key == pg.K_KP3:
                self.right_j1 = False
            if event.key == pg.K_KP4:
                self.left_j2 = False
            if event.key == pg.K_KP6:
                self.right_j2 = False
            if event.key == pg.K_KP7:
                self.left_j3 = False
            if event.key == pg.K_KP9:
                self.right_j3 = False

    # Move the joints
    def move_arm(self):
        if self.left_j2:
            self.rotate_j2()
        if self.right_j2:
            self.rotate_j2(-1)
        if self.left_j1:
            self.rotate_j1(1)
        if self.right_j1:
            self.rotate_j1(-1)
        if self.left_j3:
            self.rotate_j3(-1)
        if self.right_j3:
            self.rotate_j3(1)

