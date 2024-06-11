import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

file_path = '/content/execution_times.csv'
data = pd.read_csv(file_path)

def theoretical_complexity(v, e, coef):
    return coef * (e + v * np.log2(v))

v_values = [1024, 4096, 16384]  # 2^10, 2^12, 2^14
for v in v_values:
    subset = data[data['v'] == v]
    X = subset['e'].values.reshape(-1, 1)
    y = subset['time'].values

    model = LinearRegression()
    model.fit(X, y)
    y_pred = model.predict(X)
    coef = model.coef_[0] 
    theoretical_y = theoretical_complexity(v, subset['e'].values, coef)
    
    plt.figure(figsize=(10, 8))
    plt.scatter(X, y, label=f"Empírico v = {v}")
    plt.plot(X, y_pred, label=f"Ajuste lineal para v = {v}")
    plt.plot(X, theoretical_y, label=f"Teórico O(e + v log v) para v = {v}", linestyle='dashed')

    plt.xlabel("Número de aristas (e)")
    plt.ylabel("Tiempo de ejecución (segundos)")
    plt.legend()
    plt.title(f"Comparación Empírica y Teórica para v = {v}")
    plt.grid(True)

    plt.savefig(f'execution_time_v_{v}.png')
    plt.show()

    slope = model.coef_[0]
    intercept = model.intercept_
    print(f"v = {v}: slope = {slope}, intercept = {intercept}")
