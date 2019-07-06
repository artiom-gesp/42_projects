import matplotlib.pyplot as plt
import numpy as np
import scipy.io as sp
import scipy.optimize as opt
import time

mat = sp.loadmat('ressources/ex3data1.mat')

data = np.hstack((mat['X'], mat['y']))

X = np.array(mat['X'])
y = np.array(mat['y'])

y[y == 10] = 0
X = np.column_stack((np.ones(X.shape[0]), X))

m, n = X.shape


def get_rand_image(dataset):
    """print a single example from the dataset"""
    img_pos = np.random.randint(low=5000, size=1)
    img = np.reshape(dataset[img_pos], (20, 20))
    plt.imshow(np.transpose(img))
    plt.show()
    return dataset[img_pos]


def sigmoid(var):
    return 1 / (1 + np.exp(-var))


def one_vs_all(X, y, lmbda, num_class):
    """train params theta for each class and store them in an array of size nb_of_class x pixel_number per image"""
    theta = np.zeros((k, n))
    for i in range(num_class):
        digit_class = i
        theta[i] = opt.fmin_cg(f=get_cost, x0=theta[i], fprime=get_gradient,
                               args=(X, (y == digit_class).flatten(), lmbda),
                               maxiter=50)
    return theta


def predict(img, theta):
    """compute the likelihood for the image to belong to each class (0-9) than returns the higher percentage"""
    num_class = [None] * theta.shape[0]
    for i in range(0, 10):
        cur_theta = np.reshape(theta[i, :], (theta.shape[1], 1))
        num_class[i] = sigmoid(np.dot(img, cur_theta))[0][0]
    return np.argmax(np.array(num_class))


def get_gradient(theta, x_val, y_val, lmda):
    # m = len(y)
    temp = sigmoid(np.dot(x_val, theta)) - y_val
    # temp = np.dot(temp.T, X).T
    temp = np.dot(X.T, temp) + (lmbda / m) * theta
    return temp


def get_cost(theta, x_val, y, lmda):
    """cost function for logistic regression"""
    m = len(y)
    temp1 = np.multiply(y, np.log(sigmoid(np.dot(x_val, theta))))
    temp2 = np.multiply(1 - y, np.log(1 - sigmoid(np.dot(x_val, theta))))
    return np.sum(temp1 + temp2) / -m + lmbda / (2 * m) * np.dot(np.transpose(theta), theta)


def get_accuracy(theta, x_val, y):
    accuracy = 0
    for i in range(x_val.shape[0]):
        img = np.transpose(np.reshape(x_val[i, :], (x_val[i, :].shape[0], 1)))
        accuracy += 1 if predict(img, theta) == y[i] else 0
    print('accuracy :', 100 * accuracy / x_val.shape[0], '%')


"""lmbda for regularization and k the number of class of digits (0-9)"""
lmbda = 0.1
k = 10

y = np.reshape(y, (5000, 1))

theta = one_vs_all(X, y, lmbda, k)
get_accuracy(theta=theta, x_val=X, y=y)


"""print images of digits with corresponding prediction"""
# for i in range(100):
#     img = get_rand_image(X[:, 1:])
#     img = np.insert(img, 0, 1)
#     predict(np.transpose(np.reshape(img, (img.shape[0], 1))), theta)
# time.sleep(0.5)
