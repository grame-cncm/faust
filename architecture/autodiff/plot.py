import numpy as np
import matplotlib.pyplot as plt
import csv

file = "loss.csv"
with open(file, 'r') as csvfile:
    csvreader = csv.reader(csvfile)
    # Read the header row
    header = next(csvreader)

data = np.genfromtxt("loss.csv", delimiter=",", skip_header=1)
_, numCols = data.shape
numParams = int((numCols - 2) / 2)
iteration = data[:, 0]
loss = data[:, 1]

fig: plt.Figure
axs: list[plt.Axes]
fig, axs = plt.subplots(2 + numParams, figsize=(6, 6 + 3 * numParams))
fig.subplots_adjust(
    # left=None,
    bottom=0.05,
    # right=None,
    top=0.95,
    wspace=None,
    hspace=0.5
)

# Loss vs iteration
axs[1].plot(iteration, loss)
axs[1].grid(color="0.9")
axs[1].set_xlabel("Iteration")
axs[1].set_ylabel("Loss")
axs[1].set_title("Loss vs. Iteration")

for n in range(2, 2 + numParams):
    paramIndex = 3 + 2 * (n - 2)

    # Loss vs parameter value
    axs[0].scatter(data[:, paramIndex], loss, label=header[paramIndex])

    # Parameter value vs iteration
    axs[n].plot(iteration, data[:, paramIndex])
    axs[n].grid(color="0.9")
    axs[n].set_xlabel("Iteration")
    axs[n].set_ylabel("Parameter value")
    axs[n].set_title(f"Parameter: {header[paramIndex]}")

axs[0].grid(color="0.9")
axs[0].set_xlabel("Parameter value")
axs[0].set_ylabel("Loss")
axs[0].set_title("Loss vs. Parameter Value")
axs[0].legend()

plt.savefig("loss")
plt.show()
