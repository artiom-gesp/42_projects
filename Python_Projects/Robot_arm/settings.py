import math

WIN_WIDTH = 1920
WIN_HEIGHT = 1280

MAIN_WIN = (WIN_WIDTH, WIN_HEIGHT)

# Robot characteristics definition block :

# Length of each joint from base to end effector in cm
ROBOT_J1_LEN = 15
ROBOT_J2_LEN = 15
ROBOT_J3_LEN = 15


# Maximum distance at which the arm can grab an object in cm
ROBOT_MAX_RANGE = 35

# Angle between each joint and the joint that precedes it (consider vector (1; 0) as the the joint_0)
# Angles should be expressed in radians (from 0 to π)
# An angle of 0 rad represents two perfectly aligned joints, pointing in the same direction
ROBOT_J1_ANGLE = 3 * math.pi / 4
ROBOT_J2_ANGLE = math.pi / 2
ROBOT_J3_ANGLE = 2 * math.pi / 3

# Joints width
ROBOT_JOINT_WIDTH = 5

# End of definition block

JOINT_SCALE = WIN_WIDTH * 0.16 / ((ROBOT_J1_LEN + ROBOT_J2_LEN + ROBOT_J3_LEN) / 3)

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
