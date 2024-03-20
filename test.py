import synapc
import numpy as np
from sklearn.datasets import load_iris
data=load_iris()

X_train=data.data
y_train=data.target
y_train=y_train.astype(np.float64)


X_train=X_train[:70]
y_train=y_train[:70]
model=synapc.init(5)

synapc.add(model,4)
synapc.add(model,2)
synapc.add(model,3)

synapc.compile(model,X_train)
synapc.train(model,X_train,y_train,100)
