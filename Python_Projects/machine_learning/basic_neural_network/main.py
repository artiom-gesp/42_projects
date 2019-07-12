from basic_neural_network.neural_network import *
import time
import scipy.io as sp


def predict(net):
    for i in range(50):     # prints 50 random train_ex and the correspond prediction, really satisfying :)
        net.get_rand_image()
        time.sleep(0.7)


def vis_hidden_layer(w1):   # visualize
    for i in range(25):
        img = np.reshape(w1[i], (20, 20))
        plt.imshow(np.transpose(img))
        plt.show()


if __name__ == '__main__':
    mat = sp.loadmat('ressources/ex4data1.mat')
    data = np.hstack((mat['X'], mat['y']))

    X = np.array(mat['X'])  # training examples : 20px x 20px images mapped as rows of 400 elements
    y = np.array(mat['y'])  # corresponding label : (1 to 10, 10 being the label for 0 digits)

    y[y == 10] = 0  # provided dataset uses label 10 for 0, dit

    """load already trained params"""
    w1, w2, b1, b2 = np.load('trained_params.npy')
    weights_bias = NeuralNetwork.pack_weights_bias(w1, w2, b1, b2)

    # nn = NeuralNetwork(X, y, 1, num_iters=5000, learn_rate=0.3)    # for training
    nn = NeuralNetwork(X, y, 1, num_iters=5000, learn_rate=0.3, weights=weights_bias)  # already trained

    # nnn.my_learn()  # comment if you wish to use already learned params

    nn.get_accuracy()

    predict(nn)

    # vis_hidden_layer(w1)


