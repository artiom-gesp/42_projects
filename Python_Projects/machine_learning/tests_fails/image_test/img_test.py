import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as sn
from mpl_toolkits.mplot3d import Axes3D

if __name__ == "__main__":
    x = [elem for num_list in range(1, 1000) for elem in [num_list] * (1000 - num_list)]
    # x = [[i] * i for i in range(1, 7)]
    # distrib = [i for j in x for i in j]
    distrib = pd.DataFrame(x, columns=['dis'])
    dis2 = -10 * distrib
    print(distrib.describe())
    print(np.corrcoef((distrib['dis']), dis2['dis']))
    # print(distrib)
    (distrib['dis']**0.55).hist(bins=9)
    # print((distrib**0.5).iloc[1000:1005, 0])
    plt.show()
    # print(np.log(distrib['dis']).value_counts())