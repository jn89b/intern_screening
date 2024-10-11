"""
Step 1: First Principles
- Create a Pursuit Algorithm that will will chase a target in a 2D plane.
- The target will move in a straight line at a constant speed.

Step 2: Make it better
- How can we adjust velocity
- How can we adjust the control of the pursuer with constraints

Step 3: Make it even better
- How can we implement this in a class

"""
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import copy

from typing import List

CAPTURE_DISTANCE: float = 2.0
EVADER_VELOCITY: float = 5.0

"""
Implement the algorithm here
"""


def pure_pursuit_algorithm(pursuer_position: np.ndarray,
                           target_position: np.ndarray) -> tuple:
    """
    Implement the pursuit algorithm
    It will return the heading command for the pursuer
    and a velocity command (magnitude) for now keep velocity constant

    """
    # Calculate the heading command, keep velocity constant
    heading_cmd = 0.0
    vel_cmd = 10.0

    return vel_cmd, heading_cmd


def is_close(pursuer_position: np.ndarray,
             target_position: np.ndarray) -> bool:
    """
    Check if the pursuer is close to the target
    return True if close
    """

    distance = 100
    return False


def move(position: np.ndarray,
         velocity: np.ndarray,
         heading_cmd_rad: float,
         dt: float) -> np.ndarray:
    """
    Move the position of the target based on the velocity and time.
    Position is a 2d array that consists of x, y, and heading
    """
    position[0] += velocity * np.cos(position[2]) * dt
    position[1] += velocity * np.sin(position[2]) * dt
    position[2] += heading_cmd_rad * dt

    return position


def plot_simulation(history_pursuer: List[np.ndarray],
                    history_evader: List[np.ndarray]) -> None:
    """
    Plot the simulation
    """
    fig, ax = plt.subplots()
    ax.plot([x[0] for x in history_pursuer],
            [x[1] for x in history_pursuer],
            label='Pursuer',
            color='red')
    ax.plot([x[0] for x in history_evader],
            [x[1] for x in history_evader],
            label='Evader',
            color='blue')

    ax.legend()

    # plots the velocity and heading
    fig, ax = plt.subplots()
    ax.plot([np.rad2deg(x[2]) for x in history_pursuer],
            label='Pursuer Heading',
            color='red')
    ax.plot([np.rad2deg(x[2]) for x in history_evader],
            label='Evader Heading',
            color='blue')
    ax.legend()


def sim() -> None:

    dt: float = 0.05
    start_time: float = 0.0
    end_time: float = 10.0

    pursuer_position: np.array = np.array([-15.0,
                                           -15.0,
                                           np.deg2rad(45.0)])

    evader_position: np.array = np.array([0.0,
                                          0.0,
                                          np.deg2rad(0.0)])

    num_steps = int((end_time - start_time) / dt)

    history_pursuer = []
    history_evader = []

    for i in range(num_steps):

        # Implement the correct pursuit algorithm HERE
        vel_cmd, heading_cmd_rad = pure_pursuit_algorithm(
            pursuer_position, evader_position)

        pursuer_position = move(pursuer_position,
                                vel_cmd,
                                heading_cmd_rad,
                                dt)

        evader_position = move(evader_position,
                               EVADER_VELOCITY,
                               0.0,
                               dt)

        history_evader.append(copy.deepcopy(evader_position))
        history_pursuer.append(copy.deepcopy(pursuer_position))

        # Implement the correct logic to check if the pursuer has captured the evader
        if is_close(pursuer_position, evader_position):
            print("Captured")
            break

    # logging data to plot
    df = pd.DataFrame(history_pursuer, columns=['x', 'y', 'heading'])
    df.to_csv('pursuer.csv', index=False)

    df = pd.DataFrame(history_evader, columns=['x', 'y', 'heading'])
    df.to_csv('evader.csv', index=False)

    plot_simulation(history_pursuer, history_evader)
    plt.show()


if __name__ == '__main__':
    sim()
