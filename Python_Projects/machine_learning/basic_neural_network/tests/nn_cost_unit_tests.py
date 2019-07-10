import sys
import os
sys.path.append("..")
import basic_neural_network.neural_network as nn
import numpy as np
import scipy.io as sp
import pandas as pd

mat = sp.loadmat(os.getcwd() + '/ressources/ex4data1.mat')
data = np.hstack((mat['X'], mat['y']))

X = np.array(mat['X'])  # training examples : 20px x 20px images mapped as rows of 400 elements
y = np.array(mat['y'])  # corresponding label : (1 to 10, 10 being the label for 0 digits)

# y[y == 10] = 0

test_theta = sp.loadmat(os.getcwd() + '/ressources/ex4weights.mat')

theta_one = np.array(test_theta['Theta1'])
theta_two = np.array(test_theta['Theta2'])

weights_one = theta_one[:, 1:]
weights_two = theta_two[:, 1:]

bias_one = np.reshape(theta_one[:, 0], (1, weights_one.shape[0]))
bias_two = np.reshape(theta_two[:, 0], (1, weights_two.shape[0]))

weights_bias = [weights_one, weights_two, bias_one, bias_two]

# nnn = nn.NeuralNetwork(X, y, 1, weights_bias)
nnn = nn.NeuralNetwork(X, y, 1)

# print(nn.NeuralNetwork.compute_cost(nnn.weights_bias, nnn.train_ex, y, 1))  # expected 0.3837

# res = nnn.compute_gradient()
print(nnn.learn_param())

# test = pd.get_dummies(y.flatten())
# test = np.array(test)
# print(test[0])