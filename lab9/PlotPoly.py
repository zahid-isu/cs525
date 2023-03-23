import numpy as np
import string as str
import matplotlib.pyplot as plt

def PlotPoly():
    # First, figure out how many floats there are
    fid = open('poly.data', 'r')
    NumPts = 0
    while True:
        line = fid.readline()
        if not line: break
        NumPts = NumPts+1
    fid.close()

    # Second, read-in all the floats
    x = np.zeros(NumPts,dtype=float)
    y = np.zeros(NumPts,dtype=float)
    fid = open('poly.data', 'r')
    for k in range(0,NumPts):
        linestring = fid.readline()
        #linelist = str.split(linestring)
        linelist = linestring.split(',')
        x[k] = float(linelist[0])
        y[k] = float(linelist[1])
    fid.close()

    # Third, plot the result
    plt.rc("font", size=16)
    plt.figure(1)
    plt.plot(x,y,linestyle="dashed",linewidth=2,marker="o",
        color="red",markersize=12)
    plt.xlim(-1.0,1.0)
    plt.xticks([-1.0,-0.5,0.0,0.5,1.0])
    ax = plt.gca(); ax.grid(True)
    plt.xlabel("x-axis",size=20)
    plt.ylabel("y-axis",size=20)
    plt.title("Polynomial Plot",size=20)
    plt.savefig('legendre.png',dpi=400,bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    PlotPoly()