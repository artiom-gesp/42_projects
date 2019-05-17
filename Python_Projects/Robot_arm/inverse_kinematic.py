import robot_arm_class as rb
import numpy as np
import math
from settings import *


def inv_ki(coord: np.array):
    # x1 = robot.first_joint_tip[0]
    # x2 = robot.second_joint_tip[0]]
    len_origin_ee = math.sqrt(coord[0] ** 2 + coord[1] ** 2)
    origin_angle = math.acos(coord[0] / len_origin_ee)\
                   + math.acos((len_origin_ee ** 2 + ROBOT_J1_LEN ** 2
                                - ROBOT_J2_LEN ** 2) / (2 * len_origin_ee * ROBOT_J1_LEN))
    second_angle = math.acos((ROBOT_J1_LEN**2 + ROBOT_J2_LEN**2 - len_origin_ee**2) / (2 * ROBOT_J1_LEN * ROBOT_J2_LEN))
    return origin_angle, second_angle
