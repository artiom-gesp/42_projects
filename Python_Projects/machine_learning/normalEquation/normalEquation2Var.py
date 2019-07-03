import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def get_model_accuracy(data_size, trained_model, x_val, y_val):
    prediction = trained_model[0] + trained_model[1] * x_val[:, 0] + trained_model[2] * x_val[:, 1]
    MAPE = np.sum(100 * (np.abs((y_val - prediction) / y_val))) / data_size
    print('model accuracy : ', 100 - int(MAPE), '%')
    return prediction


data = pd.read_csv('ressources/ex1data2.txt', sep=",", header=None)
data.columns = ["x_size", "x_room", "y"]

x = data[['x_size', 'x_room']].values
y = np.array(data['y'])

data_size = x.shape[0]
x_plus_one = np.column_stack((np.ones(data_size), x))

trainedModel = np.dot(np.linalg.inv(np.dot(np.transpose(x_plus_one), x_plus_one)), np.dot(np.transpose(x_plus_one), y))
print('trained features : ', trainedModel)

x_axis = np.linspace(0, 25, 100)
slope = trainedModel[1] * x_axis + trainedModel[0]

get_model_accuracy(data_size, trainedModel, x, y)
# plt.scatter(x, y)
# plt.plot(x_axis, slope)
# plt.show()
