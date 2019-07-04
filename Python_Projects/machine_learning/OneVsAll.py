import matplotlib.pyplot as plt
import numpy as np
import scipy.io as sp
import scipy.optimize as opt
import time

mat = sp.loadmat('ex3/ex3data1.mat')

data = np.hstack((mat['X'], mat['y']))

X = np.array(mat['X'])
y = np.array(mat['y'])

y[y == 10] = 0
X = np.column_stack((np.ones(X.shape[0]), X))

m, n = X.shape


def get_rand_image(dataset):
    img_pos = np.random.randint(low=5000, size=1)
    img = np.reshape(dataset[img_pos], (20, 20))
    plt.imshow(np.transpose(img))
    plt.show()
    return dataset[img_pos]


def sigmoid(var):
    return 1 / (1 + np.exp(-var))


def one_vs_all(X, y, lmbda, num_class):
    theta = np.zeros((k, n))
    for i in range(num_class):
        digit_class = i
        theta[i] = opt.fmin_cg(f=get_cost, x0=theta[i], fprime=get_gradient,
                               args=(X, (y == digit_class).flatten(), lmbda),
                               maxiter=50)
    return theta


def predict(img, theta):
    num_class = [None] * theta.shape[0]
    for i in range(0, 10):
        cur_theta = np.reshape(theta[i, :], (theta.shape[1], 1))
        num_class[i] = sigmoid(np.dot(img, cur_theta))[0][0]
    print(np.argmax(np.array(num_class)))


def get_gradient(theta, x_val, y_val, lmda):
    # m = len(y)
    temp = sigmoid(np.dot(x_val, theta)) - y_val
    # temp = np.dot(temp.T, X).T
    temp = np.dot(X.T, temp)
    return temp


def get_cost(theta, x_val, y, lmda):
    m = len(y)
    temp1 = np.multiply(y, np.log(sigmoid(np.dot(x_val, theta))))
    temp2 = np.multiply(1 - y, np.log(1 - sigmoid(np.dot(x_val, theta))))
    return np.sum(temp1 + temp2) / -m


lmbda = 0.1
k = 10

y = np.reshape(y, (5000, 1))

theta = one_vs_all(X, y, lmbda, k)

for i in range(100):
    img = get_rand_image(X[:, 1:])
    img = np.insert(img, 0, 1)
    predict(np.transpose(np.reshape(img, (img.shape[0], 1))), theta)
time.sleep(0.5)
