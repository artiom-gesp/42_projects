import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('ressources/ex2data2.txt', sep=',', header=None)
data.columns = ["test_1", "test_2", "passed_test"]

x = data[['test_1', 'test_2']].values
y = np.array(data['passed_test'])
x_pass = x[y == 1]
x_fail = x[y == 0]

data_size = y.shape[0]

plt.scatter(x_pass[:, 0], x_pass[:, 1], label="admitted")
plt.scatter(x_fail[:, 0], x_fail[:, 1], label="not admitted")
plt.legend()
plt.show()


def increase_model_capacity(x_val):
    # x_val is at this point a 2 x data_size matrix,
    # we shall create new features by mapping the matrix columns to higher dimensions
    save = x_val
    for i in range(2, 7):
        x_val = np.column_stack((x_val, save ** i))
        x_val = np.column_stack((x_val, save[:, 0] ** i * save[:, 1] ** i))
    return x_val


def sigmoid(var):
    sig = 1 / (1 + np.exp(-var))
    sig = np.minimum(sig, 0.999999)
    sig = np.maximum(sig, 0.000001)
    return sig


def logistic_regression(size, trained_model, num_iter, x_val, y_val, learn_rate, reg):
    save = 0
    for i in range(num_iter):
        hfunct = sigmoid(np.dot(x_val, trained_model))
        regularization = (reg / size) * trained_model
        trained_model -= (learn_rate / size) * np.dot(np.transpose(x_val), (hfunct - y_val))
        trained_model += regularization
        if not np.isfinite(trained_model[0]):
            return save
        save = np.copy(trained_model)
    return trained_model


def get_accuracy(size, x_val, trained_model):
    accuracy = np.zeros((size, 1))

    test = sigmoid(np.dot(x_val, trained_model))
    test[test > 0.5] = 1
    test[test <= 0.5] = 0
    accuracy[test == np.reshape(y, (size, 1))] = 1
    return np.sum(accuracy)


x = increase_model_capacity(x)
x_add_ones = np.column_stack((np.ones(data_size), x))

theta = np.random.uniform(-100, 100, [x_add_ones.shape[1], 1])
trainedModel = logistic_regression(data_size, theta, 1000000, x_add_ones, np.reshape(y, (y.shape[0], 1)), 0.01, 0.1)

print('trained features : ', trainedModel)
print('Accuracy : ', get_accuracy(data_size, x_add_ones, trainedModel), '%')