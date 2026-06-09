import csv
import matplotlib.pyplot as plt

# --- read the data ---
mileages, prices = [], []
with open("data.csv") as f:
    reader = csv.reader(f)
    next(reader)  # skip the header row (km,price)
    for km, price in reader:
        mileages.append(float(km))
        prices.append(float(price))

# --- read the thetas ---
# assumes the file has theta0 on line 1 and theta1 on line 2
with open("theta.txt") as f:
    theta0 = float(f.readline())
    theta1 = float(f.readline())

# --- plot ---
plt.scatter(mileages, prices, color="blue", label="data")

# the regression line: just two endpoints are enough for a straight line
x_min, x_max = min(mileages), max(mileages)
y_min = theta0 + theta1 * x_min
y_max = theta0 + theta1 * x_max
plt.plot([x_min, x_max], [y_min, y_max], color="red", label="regression")

plt.xlabel("Mileage (km)")
plt.ylabel("Price")
plt.title("Linear regression")
plt.legend()
plt.show()