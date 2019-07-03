import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('ressources/ex2data1.txt', sep=',', header=None)
data.columns = ["exam_1", "exam_2", "admit"]

x = data[['exam_1', 'exam_2']].values
y = np.array(data['admit'])
x_admit = x[y == 1]
x_fail = x[y == 0]

data_size = y.shape[0]
x_add_ones = np.column_stack((np.ones(data_size), x))


def sigmoid(var):
    sig = 1 / (1 + np.exp(-var))
    sig = np.minimum(sig, 0.999999)
    sig = np.maximum(sig, 0.000001)
    return sig


def cost_function(size, x_val, y_val, trained_model):
    trained_model = np.reshape(trained_model, (len(trained_model), 1))
    hfunct = sigmoid(np.dot(x_val, trained_model))
    cost = np.sum(-y_val * np.log(hfunct) - (1 - y_val) * np.log(1 - hfunct)) / size
    return cost


def logistic_regression(size, trained_model, num_iter, x_val, y_val, learn_rate):
    for i in range(num_iter):
        hfunct = sigmoid(np.dot(x_val, trained_model))
        trained_model -= (learn_rate/size) * np.dot(np.transpose(x_val), (hfunct - y_val))
    return trained_model


def get_accuracy(size, x_val, trained_model):
    accuracy = np.zeros((size, 1))

    test = sigmoid(np.dot(x_val, trained_model))
    test[test > 0.5] = 1
    test[test <= 0.5] = 0
    accuracy[test == np.reshape(y, (size, 1))] = 1
    return np.sum(accuracy)


theta = np.random.uniform(-100, 100, [x_add_ones.shape[1], 1])

trainedModel = logistic_regression(data_size, theta, 1500000, x_add_ones, np.reshape(y, (y.shape[0], 1)), 0.1)

plot_x = np.linspace(min(x[:, 0]) - 2, max(x[:, 0]) + 2, num=100)
plot_y = (-1/trainedModel[2]) * (trainedModel[1] * plot_x + trainedModel[0])
plt.plot(plot_x, plot_y)

plt.scatter(x_admit[:, 0], x_admit[:, 1], label="admitted")
plt.scatter(x_fail[:, 0], x_fail[:, 1], label="not admitted")

plt.legend()
plt.show()

print('trained features : ', trainedModel)
print('Accuracy : ', get_accuracy(data_size, x_add_ones, trainedModel), '%')
