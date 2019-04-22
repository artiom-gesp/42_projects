import numpy as np
from mpl_toolkits import mplot3d
from skimage import io
import matplotlib.pyplot as plt

fig = plt.figure()
x = y = np.linspace(-5,5,10)
X, Y = np.meshgrid(x, y)
ax = plt.axes(projection='3d')
print (X, '\n\n')
print (Y, '\n\n')
Z = np.power(X,2) + np.power(Y,2)
print (x)
zline = np.linspace(0, 15, 1000)
xline = np.sin(zline)
yline = np.cos(zline)
#ax.plot(x, y, z)
ax.plot_surface(Y, X, Z)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
plt.show(block=True)
