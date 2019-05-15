import robot_arm_class as rb
import numpy as np

def inv_ki(robot: rb.RobotArm, coord: np.array, max_iter : int):
    x1 = robot.first_joint_tip[0]
    x2 = robot.second_joint_tip[0]
    x3 = robot.third_joint_tip[0]
    theta = np.array(1, 1, 1)
    base_x1 = -246
    cost = x1 -
    for i in max_iter:
        theta[0] -= theta[0]
        theta[1] -= theta[1]
        theta[2] -= theta[2]

