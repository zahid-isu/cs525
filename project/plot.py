import matplotlib.pyplot as plt
import numpy as np

""" This routine takes input from the output txt file and plots the graph 
    of time taken vs number of nodes.
"""

def get_node_time():
    with open('out1.txt', 'r') as f: # change the file name for n
        lines = f.readlines()
        nodes = []
        time_taken = []
        for line in lines:
            if line.startswith('mpiexec'):
                nodes.append(int(line.split(' ')[2]))
            if line.startswith('Time taken'):
                time_taken.append(float(line.split(' ')[2]))

    return nodes, time_taken

def plot_graph(nodes, time_taken):
    # bar plot only the nodes at x-axis
    plt.bar(np.arange(len(nodes)), time_taken, align='center', width=0.4)
    plt.xlabel('Number of processes (n)')
    plt.ylabel('Time taken (ms)')
    plt.xticks(np.arange(len(nodes)), nodes)
    plt.title('Run time vs Number of processes (No. of cities = 8))')
    plt.savefig('plot_8cities.png', bbox_inches='tight', dpi=1000)
    # plt.show()



if __name__== "__main__":
    nodes, time_taken = get_node_time()
    plot_graph(nodes, time_taken)


