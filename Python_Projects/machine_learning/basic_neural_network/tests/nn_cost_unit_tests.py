import os
import importlib
import sys
sys.path.append("..")
import basic_neural_network.neural_network as nn
importlib.reload(nn)
import numpy as np
import scipy.io as sp
import time

mat = sp.loadmat(os.getcwd() + '/ressources/ex4data1.mat')
data = np.hstack((mat['X'], mat['y']))

X = np.array(mat['X'])  # training examples : 20px x 20px images mapped as rows of 400 elements
y = np.array(mat['y'])  # corresponding label : (1 to 10, 10 being the label for 0 digits)

y[y == 10] = 0

test_theta = sp.loadmat(os.getcwd() + '/ressources/ex4weights.mat')

theta_one = np.array(test_theta['Theta1'])
theta_two = np.array(test_theta['Theta2'])

weights_one = theta_one[:, 1:]
weights_two = theta_two[:, 1:]

bias_one = theta_one[:, 0]
bias_two = theta_two[:, 0]

weights_bias = nn.NeuralNetwork.pack_weights_bias(weights_one, weights_two, bias_one, bias_two)
weights_size = [weights_one.shape, weights_two.shape]


def check_pack_unpack(w1, w2, b1, b2):
    pack = nn.NeuralNetwork.pack_weights_bias(w1, w2, b1, b2)
    uw1, uw2, ub1, ub2 = nn.NeuralNetwork.unpack_weights_bias(pack, w1.shape, w2.shape)
    print(np.array_equal(w1, uw1))
    print(np.array_equal(w2, uw2))
    print(np.array_equal(b1, ub1))
    print(np.array_equal(b2, ub2))


w1, w2, b1, b2 = np.load('trained_params.npy')
params = nn.NeuralNetwork.pack_weights_bias(w1, w2, b1, b2)
# check_pack_unpack(weights_one, weights_two, bias_one, bias_two)
nnn = nn.NeuralNetwork(X, y, 1, params, num_iters=2000)
# nnn.my_learn()
nnn.get_accuracy()
for i in range(50):
    nnn.get_rand_image()
# nnn = nn.NeuralNetwork(X, y, 1, weights_bias)
# res_0 = nn.NeuralNetwork.nnGrad(nn_params, 400, 25, 10, X, y, 1)
# print(nn.NeuralNetwork.compute_cost(nnn.weights_bias, nnn.train_ex, nnn.labels, 1, weights_size))  # expected 0.3837

# res = nnn.compute_gradient(weights_bias, X, y, 1, weights_size)
# nnn.learn_param()
# nnn.my_learn()
# print(res)

