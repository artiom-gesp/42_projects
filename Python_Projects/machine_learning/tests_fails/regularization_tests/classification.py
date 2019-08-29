import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import SGDClassifier
from sklearn.utils import shuffle
from sklearn.preprocessing import PolynomialFeatures
import plotly.graph_objs as go
import plotly.plotly as ply
import time

rand = np.random.rand(100)

g_1 = 50 * rand[50:] + 300
g_2 = 50 * rand[:50] + 32

y = np.ones((100,))
y[:50] = 0

X = np.hstack((g_1, g_2))
X = np.vstack((range(100), X)).T

X, y = shuffle(X, y)

poly = PolynomialFeatures(1)
X = poly.fit_transform(X)

# for i in range(1, 500):
#     plt.scatter(X[:, 1], X[:, 2])
#
#     clf = SGDClassifier(loss='log', max_iter=i, tol=1e-3)
#
#     clf.fit(X, y)
#
#     theta = (clf.coef_).flatten()
#
#     plt.plot(range(100), -(theta[0] + theta[1] * range(100)) / theta[2])
#
#     plt.show()
#     time.sleep(0.2)

clf = SGDClassifier(loss='log', max_iter=1000, tol=1e-3)

clf.fit(X, y)

theta = (clf.coef_).flatten()

data = [go.Scatter3d(x=X[:, 1], y=X[:, 2], z=clf.predict(X))]
ply.plot(data, filename='test')
