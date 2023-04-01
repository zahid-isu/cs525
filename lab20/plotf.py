
"""
This script reads the data file quadrature1.data, quadrature2.data, quadrature3.data, quadrature4.data  and plots the results.
The data file contains the subintervals used in the adaptive quadrature.
The script also plots the function and the subintervals.
The script is modified from the lecture notes of Prof.Luo.
"""


def plotf ():
    for i in range (1, 5): # 1, 2, 3, 4 threads
        print(" Plotting for thread number = ", i)
        # First , figure out how many intervals there are
        fid = open(f'quadrature{i}.data', 'r')
        NumIntervals = 0;
        while True:
            line = fid.readline ()
            if not line: break
            NumIntervals = NumIntervals +1
        fid.close ()

        import numpy as np; import string as str;
        import matplotlib.pyplot as plt

        color_dict = {1: 'b', 2: 'r', 3: 'g', 4: 'm'} # colors for each thread number

        # Second , read -in all the floats
        a = np.zeros ( NumIntervals , dtype = float )
        b = np.zeros ( NumIntervals , dtype = float )
        print("NumIntervals = ", NumIntervals)

        fid = open(f'quadrature{i}.data', 'r')
        for k in range (0, NumIntervals ):
            linestring = fid. readline ()
            linelist = linestring . split ()
            a[k] = float ( linelist [0])
            b[k] = float ( linelist [1])
        fid.close ()
        print("a = ", a)
        print("b = ", b)

        # Third , plot the result
        plt.rc("font", size =16);
        plt.figure (1)
        for k in range (0, NumIntervals ):
            color = color_dict.get(int(a[k]), 'b')
            plt.plot([a[k],b[k]], [- float (k),-float (k)], color =color , linewidth =2);
        plt.title(" Subintervals used in adaptive quadrature ")
        plt.axis("off")
        plt.savefig (f'plot/adapt_quad1_th-{i}_tole-5.png', dpi =400 , bbox_inches ='tight')
        # Fourth plot function with intervals
        xtmp = np.zeros (5*NumIntervals , dtype = float)
        xs = 0
        for k in range (0, NumIntervals):
            h = b[k]-a[k]
            xtmp[xs +0] = a[k]
            xtmp[xs +1] = a[k ]+0.25* h
            xtmp[xs +2] = a[k ]+0.5* h
            xtmp[xs +3] = a[k ]+0.75* h
            xtmp[xs +4] = b[k]
            xs = xs +5
        xsorted = np.unique(xtmp);
        fsorted = func( xsorted );
        xfine = np.linspace( -2.0 ,4.0 ,1001);
        ffine = func( xfine );
        plt.rc("font", size =16);
        plt.figure(0)
        plt.plot(xfine ,ffine , color ='b', linewidth =2);
        plt.plot(xsorted ,fsorted ,'o',color ='r',linewidth =2);
        plt.plot(xsorted , -1.1+0.0* xsorted ,'k|',markersize =10);
        plt.xlim(-2.1,4.1)
        plt.ylim(-1.55 ,1.55)
        plt.xticks(np.linspace (-2.0 ,4.0 ,7))
        plt.yticks(np.linspace (-1.5 ,1.5 ,7))
        plt.savefig(f'plot/adapt_quad2_th-{i}_tole-5.png', dpi =400 , bbox_inches ='tight')
        print(" Plotting done. ")
        plt.show();

def func(x):
    import numpy as np
    f = np.exp (-(10.0*x)**2)+np.sin(x)
    return f

if __name__ == "__main__":
    plotf()