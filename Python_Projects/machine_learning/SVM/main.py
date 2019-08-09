import pandas as pd
import scipy.io as spy
import matplotlib.pyplot as plt
import matplotlib.colors as mplcolors
import numpy as np
import svm

if __name__ == "__main__":
    data = spy.loadmat('ressources/ex6data1.mat')
    X = np.array(data['X'])
    print(X.mean(axis=0), X[:,1].mean())
    print(X.std(axis=0))
    labels = np.array(data['y'])
    labels[labels == 0] = -1
    print('lab ', labels.shape)
    y = ['red' if i == 1 else 'blue' for i in labels]
    colors = ['red', 'blue']
    plt.scatter(x=X[:, 0], y=X[:, 1], c=y)
    plt.show()
    my_svm = svm.SVM(learn_rate=0.01, reg_param=0.03, epoch=1000)
    my_svm.fit(X, labels, normalize=True)
    my_svm.run_svm()
    print(my_svm.get_prediction(X, labels))
