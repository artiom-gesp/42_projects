import matplotlib.pyplot as plt
import numpy as np
import scipy.io as sp
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
import time

mat = sp.loadmat('ressources/ex5data1.mat')


poly = PolynomialFeatures(1)

X = poly.fit_transform(np.array(mat['X']))
y = np.array(mat['y'])
Xtest = poly.fit_transform(np.array(mat['Xtest']))
ytest = np.array(mat['ytest'])
Xval = poly.fit_transform(np.array(mat['Xval']))
yval = np.array(mat['yval'])

print(X.shape)
plt.scatter(X[:, 1], y)

y[y == 10] = 0

m, n = X.shape

model = LinearRegression()

model.fit(X, y)
params = model.get_params()


def plot_train_test_error(cost_function, test_set, train_set):
    y = [cost_function(train_set[:i, :]) for i in range(2, train_set.shape[0])]
    print(y)
    plt.plot(range(train_set.shape[0]), y)
    plt.show()


x_graph = np.linspace(-50, 50, 100)
x_pl = poly.fit_transform(x_graph.reshape(-1, 1))
# print(X, x_pl)
y_graph = model.predict(x_pl)
# y_graph = [model.predict(x) for x in x_graph]
plt.plot(x_graph, y_graph, 'r')
plt.show()

# plot_train_test_error(model.score, Xtest, X)
error = []
for i in range(1, 20):
    poly = PolynomialFeatures(i)

    X = poly.fit_transform(np.array(mat['X']))
    y = np.array(mat['y'])
    Xtest = poly.fit_transform(np.array(mat['Xtest']))
    ytest = np.array(mat['ytest'])

    model = LinearRegression()

    model.fit(X, y)
    params = model.get_params()


    x_graph = np.linspace(-50, 50, 100)
    x_pl = poly.fit_transform(x_graph.reshape(-1, 1))
    y_graph = model.predict(x_pl)

    plt.scatter(Xtest[:, 1], ytest)
    plt.plot(x_graph, y_graph, 'r')

    error.append(model.score(Xtest, ytest))

    plt.show()
    print(i)
    time.sleep(1)

plt.plot(range(1, 20), error)
plt.show()
