import numpy as np

class SVM:
    """
        Basic svm class for binary classification
    """
    def __init__(self, learn_rate: float, reg_param: float, epoch:int):
        self.learn = learn_rate
        self.reg_param = reg_param
        self.epoch = epoch
        self.X = None
        self.X_dim = ()
        self.y = None
        self.coef = None

    def fit(self, X:np.array, y:np.array, normalize = False):
        if np.isnan(X).any() or np.isnan(y).any():
            raise Exception('DataSet should not contain NaN values')
        self.X_dim = X.shape
        self.X = X if not normalize else (X - X.mean(axis=0)) / X.std(axis=0)
        self.X = np.hstack((np.ones((self.X_dim[0],1)), self.X))
        self.y = y
        print(self.X.shape[1])
        self.coef = np.random.rand(1, self.X.shape[1])

    def get_score(self, X, y):
        return np.sum(self.get_prediction(X, y)) + self.reg_param * np.dot(self.coef, self.coef.T)

    def get_prediction(self, X, y):
        X = np.hstack((np.ones((X.shape[0], 1)), X))
        print(X.shape, self.X.shape, y.shape, self.y.shape)
        if X.shape != self.X.shape or y.shape != self.y.shape:
            raise Exception('Wrong dimensions')
        f_x = np.dot(X, self.coef.T)
        y_x_f = y * f_x
        pred = [0 if val >= 1 else 1 - val for val in y_x_f]
        return pred

    def
    def run_svm(self):
        for i in range(self.epoch):
            self.coef -= np.dot(-self.y.T, self.X) if self.get_score()

# distance from vector u to vector v = ||u|| - ((v . u) / ||v||.||u||)