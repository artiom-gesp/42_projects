import numpy as np
import matplotlib.pyplot as plt
import scipy.io as sp
import pandas as pd


class NeuralNetwork:

    def __init__(self, train_ex, labels, reg, theta: list = None):
        self.input_layer_size = 400
        self.hidden_layer_size = 25
        self.num_labels = 10
        self.theta = self.init_theta(theta)  # theta = [np.array(), np.array()]
        try:
            """add bias column to training examples"""
            self.train_ex = np.column_stack((np.ones(train_ex.shape[0]), train_ex))
        except Exception:
            print("Error adding bias column to training examples, please verify your input")
            exit(-1)
        self.labels = labels
        self.reg = reg  # regularization coefficient for cost and gradient

    def init_theta(self, theta: list = None) -> list:
        """randomly initialize theta if no (correct) parameters were provided"""
        if not theta:
            init_1 = np.sqrt(6) / np.sqrt(self.input_layer_size + self.hidden_layer_size)
            init_2 = np.sqrt(6) / np.sqrt(self.hidden_layer_size + self.num_labels)
            theta_1 = np.random.uniform(-init_1, init_1, (self.hidden_layer_size, self.input_layer_size + 1))
            theta_2 = np.random.uniform(-init_2, init_2, (self.num_labels, self.hidden_layer_size + 1))
            print(init_1, init_2)
            return [theta_1, theta_2]
        try:
            if (theta[0].shape != (self.hidden_layer_size, self.input_layer_size + 1) \
                    or theta[1].shape != (self.num_labels, self.hidden_layer_size + 1)):
                print("Incorrect params shape")
                exit(-1)
        except Exception:
            print('Incorrect parameters')
            exit(-1)
        return theta

    @staticmethod
    def sigmoid(x, derivative=False):
        if derivative:
            return np.exp(-x) / (1 + np.exp(-x))**2
        return 1 / (1 + np.exp(-x))

    @staticmethod
    def forward_prop(theta, train_ex):
        num_train_ex = train_ex.shape[0]
        theta_1 = theta[0]  # 25 * 401
        theta_2 = theta[1]  # 10 * 26

        a_1 = NeuralNetwork.sigmoid(np.dot(train_ex, theta_1.T))    # 5000 * 25
        a_1 = np.hstack((np.ones((num_train_ex, 1)), a_1))  # 5000 * 26

        return NeuralNetwork.sigmoid(np.dot(a_1, theta_2.T))    # 5000 * 10

    @staticmethod
    def compute_cost(theta, train_ex, labels, reg):
        """cost function of neural network"""
        num_train_ex = train_ex.shape[0]
        theta_1 = theta[0]
        theta_2 = theta[1]

        y = pd.get_dummies(labels.flatten())    # 5000 * 1
        h = NeuralNetwork.forward_prop(theta, train_ex)     # 5000 * 10

        temp1 = np.multiply(y, np.log(h))     # 5000 * 10
        temp2 = np.multiply(1 - y, np.log(1 - h))     # 5000 * 10
        cost = np.sum(temp1 + temp2)    # 1 * 1

        reg_thet_1 = np.sum(theta_1[:, 1:]**2)
        reg_thet_2 = np.sum(theta_2[:, 1:]**2)

        return np.sum(cost / (-num_train_ex)) + reg / (2.0 * num_train_ex) * (reg_thet_1 + reg_thet_2)
