import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import scipy.optimize as opt


class NeuralNetwork:

    def __init__(self, train_ex, labels, reg, weights: list = None, num_iters = 1500, learn_rate = 0.3):
        self.input_layer_size = 400
        self.hidden_layer_size = 25
        self.num_labels = 10  # output layer size
        self.weights_bias = self.init_weights_biases(weights)  # weights = [np.array(),... ,np.array()]

        self.train_ex = train_ex
        self.labels = labels

        self.reg = reg  # regularization coefficient for cost and gradient
        self.num_iters = num_iters
        self.learn_rate = learn_rate

    def is_input_valid(self, w):

        w1, w2, b1, b2 = self.unpack_weights_bias(w, (self.hidden_layer_size, self.input_layer_size),
                                            (self.num_labels, self.hidden_layer_size))
        try:  # check user provided weight_bias list
            error_flag = False
            if w1.shape != (self.hidden_layer_size, self.input_layer_size):
                error_flag = True
            if w2.shape != (self.num_labels, self.hidden_layer_size):
                error_flag = True
            if b1.shape != (self.hidden_layer_size,):
                error_flag = True
            if b2.shape != (self.num_labels,):
                error_flag = True

            if error_flag:
                print("Incorrect params shape")
                return False
        except Exception:
            print('Incorrect parameters')
            return False
        return True

    def init_weights_biases(self, weights = None) -> np.array:
        """randomly initialize weights if no (correct) parameters were provided"""
        if weights is None:  # if no weights_bias list were provided, initialize it randomly
            init_1 = np.sqrt(6) / np.sqrt(self.input_layer_size + self.hidden_layer_size)  # defines min/max
            init_2 = np.sqrt(6) / np.sqrt(self.hidden_layer_size + self.num_labels)  # for each parameter's values

            w1 = np.random.uniform(-init_1, init_1, (self.hidden_layer_size, self.input_layer_size))
            w2 = np.random.uniform(-init_2, init_2, (self.num_labels, self.hidden_layer_size))

            b1 = np.random.uniform(-init_2, init_2, (self.hidden_layer_size,))
            b2 = np.random.uniform(-init_2, init_2, (self.num_labels,))

            return self.pack_weights_bias(w1, w2, b1, b2)

        if not self.is_input_valid(weights):
            print('Initializing weights randomly..')
            return self.init_weights_biases()

        return weights  # if no errors were raised, returns the same list

    @staticmethod
    def pack_weights_bias(w1, w2, b1, b2):
        param_2 = np.hstack((w2, np.reshape(b2, (b2.shape[0], 1))))

        param_1 = np.hstack((w1, np.reshape(b1, (b1.shape[0], 1))))
        param_1 = np.vstack((param_1, np.ones((1, param_1.shape[1]))))

        return np.hstack((param_1, param_2.T)).flatten()

    @staticmethod
    def unpack_weights_bias(packed_params, w_1_size: tuple, w_2_size: tuple):
        packed_params = np.reshape(packed_params, (w_1_size[0] + 1, w_1_size[1] + w_2_size[0] + 1))
        param_1 = packed_params[:-1, :(w_1_size[1] + 1)]
        param_2 = packed_params[:, (w_1_size[1] + 1):].T

        w1 = param_1[:, :w_1_size[1]]
        b1 = param_1[:, -1]

        w2 = param_2[:, :w_2_size[1]]
        b2 = param_2[:, -1]

        return w1, w2, b1, b2

    @staticmethod
    def forward_prop(weights_bias, train_ex, w_size):
        w1, w2, b1, b2 = NeuralNetwork.unpack_weights_bias(weights_bias, w_size[0], w_size[1])

        #   b1 is a row vector, added to every row of a_1
        z_1 = np.dot(train_ex, w1.T) + b1
        a_1 = NeuralNetwork.sigmoid(z_1)  # 5000 * 25

        z_2 = np.dot(a_1, w2.T) + b2
        return NeuralNetwork.sigmoid(z_2), a_1, z_2, z_1  # 5000 * 10

    @staticmethod
    def sigmoid(x, derivative=False):
        if derivative:
            # return np.exp(-x) / ((1 + np.exp(-x)) ** 2)
            return NeuralNetwork.sigmoid(x) * (1 - NeuralNetwork.sigmoid(x))
        return 1 / (1 + np.exp(-x))

    @staticmethod
    def compute_cost(weights_bias, train_ex, labels, reg, w_size):  # cost function of neural network

        num_train_ex = train_ex.shape[0]
        w1, w2, b1, b2 = NeuralNetwork.unpack_weights_bias(weights_bias, w_size[0], w_size[1])

        y = pd.get_dummies(labels.flatten())  # 5000 * 1
        h, a_1, z_2, z_1 = NeuralNetwork.forward_prop(weights_bias, train_ex, w_size)  # 5000 * 10

        temp1 = np.multiply(y, np.log(h))  # 5000 * 10
        temp2 = np.multiply(1 - y, np.log(1 - h))  # 5000 * 10
        cost = np.sum(temp1 + temp2)  # 1 * 1

        reg_cost_1 = np.sum(w1 ** 2)
        reg_cost_2 = np.sum(w2 ** 2)
        cost = np.sum(cost / (-num_train_ex)) + reg / (2.0 * num_train_ex) * (reg_cost_1 + reg_cost_2)
        return cost

    @staticmethod
    def compute_gradient(weights_bias, train_ex, labels, reg, w_size):
        """vectorized implementation of neural network backpropagation"""

        num_train_ex = train_ex.shape[0]

        w1, w2, b1, b2 = NeuralNetwork.unpack_weights_bias(weights_bias, w_size[0], w_size[1])  # current weights

        labels = pd.get_dummies(labels.flatten())   # one hot encoding of labels (5000 * 10)
        a_2, a_1, z_2, z_1 = NeuralNetwork.forward_prop(weights_bias, train_ex, w_size)

        d_2 = a_2 - np.array(labels)  # error of output layer (5000 * 10)
        d_1 = np.dot(d_2, w2)
        d_1 = np.multiply(d_1, NeuralNetwork.sigmoid(z_1, derivative=True))     # error at hidden layer (5000 * 25)

        delta_1 = d_1.T @ train_ex
        delta_2 = d_2.T @ a_1

        delta_1 /= num_train_ex  # gradient with respect to w1
        delta_2 /= num_train_ex # gradient with respect to w2

        delta_1 += (w1 * reg) / num_train_ex    # regularization
        delta_2 += (w2 * reg) / num_train_ex

        update_b2 = np.sum(d_2 / num_train_ex, axis=0)  # gradient with respect to bias units
        update_b1 = np.sum(d_1 / num_train_ex, axis=0)

        return NeuralNetwork.pack_weights_bias(delta_1, delta_2, update_b1, update_b2)

    def my_learn(self):
        """my_learn is my very basic optimization function, it updates weights during num_iters iterations
        and prints system accuracy every 100 iterations, a accuracy of 96% is to be expected with 5000+ iterations"""
        w_size = [(self.hidden_layer_size, self.input_layer_size), (self.num_labels, self.hidden_layer_size)]
        for i in range(self.num_iters):
            self.weights_bias -= self.learn_rate * NeuralNetwork.compute_gradient(self.weights_bias,
                                                                                  self.train_ex,
                                                                                  self.labels,
                                                                                  self.reg,
                                                                                  w_size)
            if i % 100 == 0:    # prints accuracy at start + every 100 steps
                self.get_accuracy()
                # saves current parameters in a .npy file
        np.save('trained_params.npy', self.unpack_weights_bias(self.weights_bias, w_size[0], w_size[1]))

    def learn_param(self):
        """this is supposed to work.. but it does not, fmin_cg losses accuracy for some reason"""
        w_size = [(self.hidden_layer_size, self.input_layer_size), (self.num_labels, self.hidden_layer_size)]
        self.weights_bias = opt.fmin_cg(f=NeuralNetwork.compute_cost, x0=self.weights_bias,
                                        fprime=NeuralNetwork.compute_gradient,
                                        args=(self.train_ex, self.labels, self.reg, w_size), maxiter=100)
        return self.weights_bias

    def get_accuracy(self):
        """for all training examples do forward prop and increment accuracy if prediction == label"""
        accuracy = 0
        m = self.train_ex.shape[0]
        w_size = [(self.hidden_layer_size, self.input_layer_size), (self.num_labels, self.hidden_layer_size)]
        res, no, na, ni = NeuralNetwork.forward_prop(self.weights_bias, self.train_ex, w_size)
        for i in range(m):
            if np.argmax(res[i]) == self.labels[i]:
                accuracy += 1
        print('accuracy :', 100 * accuracy / m, '%')

    def get_rand_image(self):
        """prints a single example from the dataset and the corresponding prediction"""
        w_size = [(self.hidden_layer_size, self.input_layer_size), (self.num_labels, self.hidden_layer_size)]
        res, no, na, ni = NeuralNetwork.forward_prop(self.weights_bias, self.train_ex, w_size)
        img_pos = np.random.randint(low=5000, size=1)
        img = np.reshape(self.train_ex[img_pos], (20, 20))
        plt.imshow(np.transpose(img))
        plt.show()
        print(res.shape)
        print(np.argmax(res[img_pos]))
