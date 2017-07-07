import numpy as np
import matplotlib.pyplot as plt

def liney(a, b, c, x):
    return (-c - a*x) / b


def main():
    fig, ax = plt.subplots()
    ax.set_xlim((-300, 300))
    ax.set_ylim((-300, 300))
    c1 = plt.Circle((-57.1429, -57.1429), 202.031, fill=False)
    c2 = plt.Circle((-5.05051, 5.05051), 71.4249, fill=False)
    ax.add_artist(c1)
    ax.add_artist(c2)
    plt.show()

main()