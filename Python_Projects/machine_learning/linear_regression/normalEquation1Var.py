import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def get_model_accuracy(size, trained_model, x_val, y_val):
    prediction = trained_model[0] + trained_model[1] * x_val
    MSE = np.sum(((y_val - prediction)**2)) / size
    print('MSE : ', MSE,)
    return prediction


data = pd.read_csv('ressources/ex1data1.txt', sep=",", header=None)
data.columns = ["x", "y"]

x = np.array(data['x'])
y = np.array(data['y'])

data_size = x.shape[0]
x_plus_one = np.column_stack((np.ones(data_size), x))

trainedModel = np.dot(np.linalg.inv(np.dot(np.transpose(x_plus_one), x_plus_one)), np.dot(np.transpose(x_plus_one), y))
print('trained features : ', trainedModel)

x_axis = np.linspace(0, 25, 100)
slope = trainedModel[1] * x_axis + trainedModel[0]

plt.scatter(x, y)
plt.plot(x_axis, slope)
plt.show()

test = np.row_stack((get_model_accuracy(data_size, trainedModel, x, y), y))
print(100 * np.sum(np.abs((y - test[0, :]) / y)) / data_size)
