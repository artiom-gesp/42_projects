import pandas as pd
import scipy.io as spy
import matplotlib.pyplot as plt
import matplotlib.colors as mplcolors
import numpy as np

if __name__ == "__main__":
    data = spy.loadmat('ressources/ex6data1.mat')
    X = np.array(data['X'])
    labels = np.array(data['y'])
    labels[labels == 0] = -1
    y = ['red' if i == 1 else 'blue' for i in labels]
    colors = ['red', 'blue']
    plt.scatter(x=X[:, 0], y=X[:, 1], c=y)
    plt.show()
