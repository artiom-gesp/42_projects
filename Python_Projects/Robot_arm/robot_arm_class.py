import pygame as pg
from settings import *
import numpy as np


class RobotArm:
    def __init__(self, window):
        # plane origin in screen coordinates
        self.base_coord = np.array([[WIN_WIDTH / 2], [WIN_HEIGHT - WIN_HEIGHT / 5]])

        # Arm base is represented by a rectangle
        self.base_surface = (int(WIN_WIDTH / 4.5), int(WIN_HEIGHT / 24))

        # create the surface representing the base
        self.robot_base = pg.Surface(self.base_surface)

        # JOINT_1 RELATED VARIABLES
        self.j1_origin = np.zeros((2, 1))
        # ee stands for end effector
        self.j1_ee = self.rotate(np.array([JOINT_SCALE * ROBOT_J1_LEN, 0]), ROBOT_J1_ANGLE)
        self.j1_angle = ROBOT_J1_ANGLE
        # screen coordinates of joint_1
        self.j1_plane_coord = np.add(self.base_coord, self.j1_ee)

        # JOINT_2 RELATED VARIABLES
        # cartesian coordinates of joint_2
        self.j2_ee = self.rotate(-self.j1_ee * ROBOT_J2_LEN / ROBOT_J1_LEN, ROBOT_J2_ANGLE)
        # basis of joint_2
        self.j2_origin = self.j1_ee
        # angle between joint_1 and joint_2
        self.j2_angle = ROBOT_J2_ANGLE
        # screen coordinates of joint_2
        self.j2_plane_origin = np.add(self.j1_plane_coord, self.j2_origin)

        # JOINT_3 RELATED VARIABLES
        self.j3_origin = self.j2_ee
        # angle between joint_2 and joint_3
        self.j3_angle = ROBOT_J3_ANGLE
        # cartesian coordinates of joint_3
        self.j3_ee = self.rotate(-self.j2_ee * ROBOT_J3_LEN / ROBOT_J2_LEN, ROBOT_J3_ANGLE)
        # screen coordinates of the origin joint_3
        self.j3_plane_origin = np.add(self.j2_plane_origin, self.j3_origin)

        # Set of variables to enable manual rotation
        self.left_j1 = False
        self.left_j2 = False
        self.right_j1 = False
        self.right_j2 = False
        self.left_j3 = False
        self.right_j3 = False

        # main window
        self.window = window

        # maximum_range of the arm
        self.max_range = (ROBOT_MAX_RANGE if ROBOT_MAX_RANGE <= (ROBOT_J1_LEN + ROBOT_J2_LEN + ROBOT_J3_LEN) else
                          ROBOT_J1_LEN + ROBOT_J2_LEN + ROBOT_J3_LEN) * JOINT_SCALE

        self.x_line = 0
        self.y_line = 0

    # do a simple rotation in space using a rotation matrix
    @staticmethod
    def rotate(coord: np.array, rad_angle: float):
        rot_matrix = np.array([[math.cos(rad_angle), -1 * math.sin(rad_angle)],
                               [math.sin(rad_angle), math.cos(rad_angle)]])
        # returns the product of the rotation matrix * the vector coordinates
        ret = np.dot(rot_matrix, coord)
        ret.shape = (2, 1)
        return ret

    # rotating joint_1 and adapt joint_2 to keep the same angle between them
    def rotate_j1(self, angle: float = (math.pi / 180)):
        if (angle > 0 and self.j1_angle + angle < math.pi) \
                or (angle < 0 < self.j1_angle + angle):
            self.j1_angle += angle
            self.j1_ee = self.rotate(self.j1_ee, angle)
            self.j2_ee = self.rotate(self.j2_ee, angle)
            self.j3_ee = self.rotate(self.j3_ee, angle)

    # rotating joint_2
    def rotate_j2(self, angle: float = (math.pi / 180)):
        if (angle > 0 and self.j2_angle + angle < math.pi) \
                or (angle < 0 < self.j2_angle + angle):
            self.j2_angle += angle
            self.j2_ee = np.array(self.rotate(self.j2_ee, angle))
            self.j3_ee = np.array(self.rotate(self.j3_ee, angle))

    # rotating joint_3
    def rotate_j3(self, angle: float = (math.pi / 180)):
        if (angle > 0 and self.j3_angle + angle < math.pi) \
                or (angle < 0 < self.j3_angle + angle):
            self.j3_angle += angle
            self.j3_ee = np.array(self.rotate(self.j3_ee, angle))

    def draw_joints(self):
        self.robot_base.fill(WHITE)
        # base_coord being the origin, base_coord - base_surface is the top left corner of the base
        self.window.blit(self.robot_base, (self.base_coord[0] - self.base_surface[0] / 2, self.base_coord[1]))
        # Transposing a cartesian coordinates plane into a computer graphics plane
        self.j1_plane_coord = np.array([[self.j1_ee[0] + self.base_coord[0]],
                                        [math.fabs(self.j1_ee[1] - self.base_coord[1])]])
        # Drawing first joint
        pg.draw.line(self.window, WHITE, self.base_coord, self.j1_plane_coord,
                     ROBOT_JOINT_WIDTH)

        # Adjusting joint_2 coordinates
        self.j2_origin = self.j1_plane_coord
        self.j2_plane_origin = (self.j2_ee[0] + self.j1_plane_coord[0],
                                (math.fabs(self.j2_ee[1]
                                           - self.j1_plane_coord[1])))

        # Drawing second joint
        pg.draw.line(self.window, WHITE, self.j2_origin, self.j2_plane_origin,
                     ROBOT_JOINT_WIDTH)

        # Adjusting joint_3 coordinates
        self.j3_origin = self.j2_plane_origin
        self.j3_plane_origin = (self.j3_ee[0] + self.j2_plane_origin[0],
                                math.fabs(self.j3_ee[1]
                                          - self.j2_plane_origin[1]))

        # Drawing third joint
        pg.draw.line(self.window, WHITE, self.j3_origin, self.j3_plane_origin,
                     ROBOT_JOINT_WIDTH)

    # Draw a line with the end effector perpendicular to the x_axis at the position of the mouse_click
    def draw_line(self):
        coord_range = math.sqrt((self.x_line - self.base_coord[0]) ** 2 + (self.base_coord[1] - self.y_line) ** 2)
        if self.y_line < self.j3_plane_origin[1] and coord_range < self.max_range:
            self.rotate_j1(math.pi / 180)
            self.rotate_j3(math.pi / 180)
        if self.y_line >= self.j3_plane_origin[1] and coord_range < self.max_range:
            self.rotate_j1(-math.pi / 180)
            self.rotate_j3(-math.pi / 180)
        if self.x_line == self.j2_plane_origin[0]:
            self.x_line, self.y_line = 0, 0

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
            self.rotate_j2(math.pi / 180)
        if self.right_j2:
            self.rotate_j2(-math.pi / 180)
        if self.left_j1:
            self.rotate_j1(math.pi / 180)
        if self.right_j1:
            self.rotate_j1(-math.pi / 180)
        if self.left_j3:
            self.rotate_j3(-math.pi / 180)
        if self.right_j3:
            self.rotate_j3(math.pi / 180)
