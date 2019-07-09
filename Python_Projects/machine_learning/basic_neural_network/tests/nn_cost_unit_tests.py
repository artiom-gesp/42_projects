import sys
import os
sys.path.append("..")
import basic_neural_network.neural_network as nn
import numpy as np
import scipy.io as sp

mat = sp.loadmat(os.getcwd() + '/ressources/ex4data1.mat')
data = np.hstack((mat['X'], mat['y']))

X = np.array(mat['X'])  # training examples : 20px x 20px images mapped as rows of 400 elements
y = np.array(mat['y'])  # corresponding label : (1 to 10, 10 being the label for 0 digits)
# y[y == 10] = 0  # original dataset has label 10 for 0 digits

X = np.column_stack((np.ones(X.shape[0]), X))   # add bias column to training examples

test_theta = sp.loadmat(os.getcwd() + '/ressources/ex4weights.mat')

theta_one = np.array(test_theta['Theta1'])
theta_two = np.array(test_theta['Theta2'])

global_theta = [theta_one, theta_two]
print(nn.NeuralNetwork.compute_cost(global_theta, X, y, 1))
# print(nn.NeuralNetwork.sigmoid(0))
print(nn.NeuralNetwork.sigmoid(0, derivative=True))

nn.NeuralNetwork(X, y, 1)