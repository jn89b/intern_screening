import pandas as pd
import numpy as np

import matplotlib.pyplot as plt

if __name__ == "__main__":
    df = pd.read_csv("pursuit.csv")
    fig, ax = plt.subplots()
    ax.plot(df["pursuer_x"], df["pursuer_y"], label="pursuer", color="red")
    ax.plot(df["evader_x"], df["evader_y"], label="evader", color="blue")
    ax.scatter(df["evader_x"].iloc[-1], df["evader_y"].iloc[-1],
               label="evader end", color="blue")
    ax.scatter(df["pursuer_x"].iloc[-1], df["pursuer_y"].iloc[-1],
               label="pursuer end", color="red")
    ax.scatter(df["evader_x"].iloc[0], df["evader_y"].iloc[0],
               label="evader start", color="blue", marker="x")
    ax.scatter(df["pursuer_x"].iloc[0], df["pursuer_y"].iloc[0],
               label="pursuer start", color="red", marker="x")
    ax.legend()

    fig, ax = plt.subplots()
    ax.plot(np.rad2deg(df["pursuer_theta"]),
            label="pursuer heading", color="red")
    ax.plot(np.rad2deg(df["evader_theta"]),
            label="evader heading", color="blue")

    ax.legend()

    fig, ax = plt.subplots()
    ax.plot(df["vel_cmd"], label="pursuer vel cmd", color="red")
    ax.legend()

    fig, ax = plt.subplots()
    ax.plot(df["heading_cmd"],
            label="pursuer heading cmd", color="blue")

    ax.legend()
    plt.show()
