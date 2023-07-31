import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("loss.csv", delimiter=",", skip_header=1)

fig: plt.Figure
ax1: plt.Axes
ax2: plt.Axes
fig, (ax1, ax2) = plt.subplots(2, figsize=(6, 8))

ax1.scatter(data[:, 3], data[:, 1])
ax1.grid(color="0.9")
ax1.set_xlabel("Parameter value")
ax1.set_ylabel("Loss")

ax2.plot(data[:, 0], data[:, 1])
ax2.grid(color="0.9")
ax2.set_xlabel("Iteration")
ax2.set_ylabel("Loss")

plt.savefig("loss")
plt.show()
