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
        self.first_joint_tip = (self.joint_len, self.joint_len)
        self.first_joint_angle = 45

        # screen coordinates of joint_1
        self.first_joint_plane_coord = (self.first_joint_tip[0] + self.base_coord[0],
                                        (math.fabs(self.first_joint_tip[1] - self.base_coord[1])))
        # base of joint_2
        self.second_joint_base = self.first_joint_tip

        # angle between joint_1 and joint_2
        self.second_joint_angle = 90
        # cartesian coordinates of joint_2
        self.second_joint_tip = (self.first_joint_tip[1], -1 * self.first_joint_tip[0])
        # screen coordinates of joint_2
        self.second_plane_coord =\
            tuple(map(operator.add, self.first_joint_plane_coord, self.second_joint_base))


        # Set of variable to enable manual rotation
        self.left_j1 = False
        self.left_j2 = False
        self.right_j1 = False
        self.right_j2 = False

        # window where to draw lines
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
        if (angle > 0 and self.first_joint_angle + angle < 135)\
                or (angle < 0 and 45 < self.first_joint_angle + angle):
            self.first_joint_angle += angle
            self.first_joint_tip = self.rotate(self.first_joint_tip, angle)
            self.second_joint_tip = self.rotate(self.second_joint_tip, angle)

    # rotating joint_2
    def rotate_j2(self, angle: int = 1):
        if (angle > 0 and self.second_joint_angle + angle < 135)\
                or (angle < 0 and 45 < self.second_joint_angle + angle):
            print('i3')
            print(self.second_joint_angle)
            self.second_joint_angle += angle
            self.second_joint_tip = self.rotate(self.second_joint_tip, angle)
            print(self.second_joint_angle)

    def draw_joints(self):
        # Resetting screen before printing
        self.window.fill(BLACK)
        self.robot_base.fill(WHITE)
        print("1", self.second_joint_angle)
        # base_coord being the origin, base_coord - base_surface is the top left corner of the base
        self.window.blit(self.robot_base, (self.base_coord[0] - self.base_surface[0] / 2, self.base_coord[1]))

        # Transposing a cartesian coordinate plane into a computer graphics planes
        self.first_joint_plane_coord = (self.first_joint_tip[0] + self.base_coord[0],
                                        (math.fabs(self.first_joint_tip[1] - self.base_coord[1])))

        # Drawing first joint
        pg.draw.line(self.window, WHITE, self.base_coord, self.first_joint_plane_coord,
                     self.joint_width)

        print("2", self.second_joint_angle)
        # Adjusting joint_2 coordinates
        self.second_joint_base = self.first_joint_plane_coord
        self.second_plane_coord = (self.second_joint_tip[0] + self.first_joint_plane_coord[0],
                                   (math.fabs(self.second_joint_tip[1]
                                              - self.first_joint_plane_coord[1])))

        # Drawing second joint
        print("3", self.second_joint_angle)
        pg.draw.line(self.window, WHITE, self.second_joint_base, self.second_plane_coord,
                     self.joint_width)

    # move joints, receives a pygame get_keys as input and pygame event
    def get_controls(self, keys, event):
        if event.type == pg.KEYDOWN:
            if event.key == pg.K_KP1:
                self.left_j1 = True
            if event.key == pg.K_KP3:
                self.right_j1 = True
            if event.key == pg.K_KP4:
                self.left_j2 = True
            if event.key == pg.K_KP6:
                print('i')
                self.right_j2 = True
        if event.type == pg.KEYUP:
            if event.key == pg.K_KP1:
                self.left_j1 = False
            if event.key == pg.K_KP3:
                self.right_j1 = False
            if event.key == pg.K_KP4:
                self.left_j2 = False
            if event.key == pg.K_KP6:
                self.right_j2 = False

    def move_arm(self):
        if self.left_j2:
            self.rotate_j2(1)
        if self.right_j2:
            self.rotate_j2(-1)
        if self.left_j1:
            self.rotate_j1(1)
        if self.right_j1:
            self.rotate_j1(-1)

