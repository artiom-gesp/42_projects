import numpy as np
import matplotlib.pyplot as plt
import scipy.io as sp
import pandas as pd
import scipy.optimize as opt


class NeuralNetwork:

    def __init__(self, train_ex, labels, reg, weights: list = None, num_iters = 1500):
        self.input_layer_size = 400
        self.hidden_layer_size = 25
        self.num_labels = 10  # output layer size
        self.weights_bias = self.init_weights_biases(weights)  # weights = [np.array(),... ,np.array()]

        self.train_ex = train_ex
        self.labels = labels

        self.reg = reg  # regularization coefficient for cost and gradient
        self.num_iters = 50

    def is_input_valid(self, weights):
        try:  # check user provided weight_bias list
            error_flag = False
            if weights[0].shape != (self.hidden_layer_size, self.input_layer_size):
                error_flag = True
            if weights[1].shape != (self.num_labels, self.hidden_layer_size):
                error_flag = True
            if weights[2].shape != (1, self.hidden_layer_size):
                error_flag = True
            if weights[3].shape != (1, self.num_labels):
                error_flag = True

            if error_flag:
                print("Incorrect params shape")
                return False
        except Exception:
            print('Incorrect parameters')
            return False
        return True

    def init_weights_biases(self, weights: list = None) -> list:
        """randomly initialize weights if no (correct) parameters were provided"""
        if not weights:  # if no weights_bias list were provided, initialize it randomly
            init_1 = np.sqrt(6) / np.sqrt(self.input_layer_size + self.hidden_layer_size)  # defines min/max
            init_2 = np.sqrt(6) / np.sqrt(self.hidden_layer_size + self.num_labels)  # for each parameter's values

            weights_1 = np.random.uniform(-init_1, init_1, (self.hidden_layer_size, self.input_layer_size))
            weights_2 = np.random.uniform(-init_2, init_2, (self.num_labels, self.hidden_layer_size))

            bias_1 = np.random.uniform(-init_2, init_2, (1, self.hidden_layer_size))
            bias_2 = np.random.uniform(-init_2, init_2, (1, self.num_labels))

            return [weights_1, weights_2, bias_1, bias_2]

        if not self.is_input_valid(weights):
            print('Initializing weights randomly..')
            return self.init_weights_biases()

        return weights  # if no errors were raised, returns the same list


    @staticmethod
    def forward_prop(weights, train_ex):
        weights_1 = weights[0]  # 25 * 400
        weights_2 = weights[1]  # 10 * 25
        bias_1 = weights[2]  # 1 * 25
        bias_2 = weights[3]  # 1 * 10

        #   bias_1 is a row vector, added to every row of a_1
        z_1 = np.dot(train_ex, weights_1.T) + bias_1
        a_1 = NeuralNetwork.sigmoid(z_1)  # 5000 * 25

        z_2 = np.dot(a_1, weights_2.T) + bias_2
        return NeuralNetwork.sigmoid(z_2), a_1, z_2, z_1  # 5000 * 10

    @staticmethod
    def sigmoid(x, derivative=False):
        if derivative:
            return np.exp(-x) / ((1 + np.exp(-x)) ** 2)
        return 1 / (1 + np.exp(-x))

    @staticmethod
    def compute_cost(weights, train_ex, labels, reg):  # cost function of neural network

        num_train_ex = train_ex.shape[0]
        weights_1 = weights[0]
        weights_2 = weights[1]

        y = pd.get_dummies(labels.flatten())  # 5000 * 1
        h, a_1, z_2, z_1 = NeuralNetwork.forward_prop(weights, train_ex)  # 5000 * 10

        temp1 = np.multiply(y, np.log(h))  # 5000 * 10
        temp2 = np.multiply(1 - y, np.log(1 - h))  # 5000 * 10
        cost = np.sum(temp1 + temp2)  # 1 * 1

        reg_cost_1 = np.sum(weights_1 ** 2)
        reg_cost_2 = np.sum(weights_2 ** 2)

        return np.sum(cost / (-num_train_ex)) + reg / (2.0 * num_train_ex) * (reg_cost_1 + reg_cost_2)

    @staticmethod
    def compute_gradient(weights_bias, train_ex, labels, reg):
        num_train_ex = train_ex.shape[0]

        weights_1 = weights_bias[0]  # 25 * 400
        weights_2 = weights_bias[1]  # 10 * 25
        bias_1 = weights_bias[2]  # 1 * 25
        bias_2 = weights_bias[3]  # 1 * 10

        delta_1 = np.zeros(weights_1.shape)
        delta_2 = np.zeros(weights_2.shape)
        update_b1 = np.zeros(bias_1.shape)
        update_b2 = np.zeros(bias_2.shape)

        labels = pd.get_dummies(labels.flatten())
        a_2, a_1, z_2, z_1 = NeuralNetwork.forward_prop(weights_bias, train_ex)

        d_2 = a_2 - np.array(labels)  # 5000 * 10
        d_1 = np.dot(d_2, weights_2)    # 5000 * 25
        d_1 = np.multiply(d_1, NeuralNetwork.sigmoid(z_1, derivative=True))

        delta_1 += d_1.T @ train_ex
        delta_2 += d_2.T @ a_1

        delta_1 /= num_train_ex
        delta_2 /= num_train_ex

        delta_1 += weights_1 * reg / num_train_ex
        delta_2 += weights_2 * reg / num_train_ex

        update_b2 = np.sum(d_2, axis=0)
        update_b1 = np.sum(d_1, axis=0)

        return [delta_1, delta_2, update_b1, update_b2]

    def learn_param(self):
        self.weights_bias = opt.fmin_cg(f=NeuralNetwork.compute_cost, x0=self.weights_bias,
                                        args=(self.train_ex, self.labels, self.reg), maxiter=200)
        return self.weights_bias
