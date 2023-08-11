import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("loss.csv", delimiter=",", skip_header=1)

fig: plt.Figure
ax1: plt.Axes
ax2: plt.Axes
fig, (ax1, ax2, ax3) = plt.subplots(3, figsize=(6, 10))

# Loss vs parameter value
ax1.scatter(data[:, 3], data[:, 1])
ax1.grid(color="0.9")
ax1.set_xlabel("Parameter value")
ax1.set_ylabel("Loss")

# Loss vs iteration
ax2.plot(data[:, 0], data[:, 1])
ax2.grid(color="0.9")
ax2.set_xlabel("Iteration")
ax2.set_ylabel("Loss")

# Parameter value vs iteration
ax3.plot(data[:, 0], data[:, 3])
ax3.grid(color="0.9")
ax3.set_xlabel("Iteration")
ax3.set_ylabel("Parameter value")

plt.savefig("loss")
plt.show()
