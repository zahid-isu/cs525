import sys
import time
from mpi4py import MPI
from itertools import permutations
from math import dist
import numpy as np

""" This script implements the dynamic tree search using MPI library of python for parallel computing.
    Documentation used for this code: https://mpi4py.readthedocs.io/en/stable/
    The inputs are the number of cities (n) and randomly generated coordinates of the cities.
    The outputs are the shortest path and the time taken (ms) to find the shortest path.
    The process0 (root node) chunks the data to other process and at the end collect the results from other processes.
    Also, it shows individual time taken by each processor.

    To run this script, use the following command at MPI terminal:
    mpiexec -n 4 python tree2.py

    The number of processes can be changed by changing the value of -n 
    The -n values I tried: [1,2,4,8,16]
    Note that every run will give different results because the cities are randomly generated.

"""


# def distance(path, cities):
#     return sum(dist(cities[path[i - 1]], cities[path[i]]) for i in range(len(cities)))
def distance(path, cities):
    d = 0
    for i in range(len(path) - 1):
        d += np.linalg.norm(cities[path[i]] - cities[path[i + 1]])
    d += np.linalg.norm(cities[path[-1]] - cities[path[0]])
    return d


def explore_tree(rank, cities, stack):
    best_path, best_distance = None, sys.float_info.max

    while stack:
        path = stack.pop()

        if len(path) == len(cities):
            path_distance = distance(path, cities)
            if path_distance < best_distance:
                best_path, best_distance = path, path_distance
        else:
            for city in set(range(len(cities))) - set(path):
                stack.append(path + (city,))

    return rank, best_path, best_distance

def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    # cities = [(1, 1), (3, 1), (2, 2), (4, 2), (1, 3), (3, 3), (2, 4), (4, 4)]
    num_cities = 8
    cities = np.random.rand(num_cities, 2)

    if rank == 0:
        all_permutations = list(permutations(range(1, len(cities))))
        stack_size = len(all_permutations) // size
        stacks = [tuple(all_permutations[i * stack_size:(i + 1) * stack_size]) for i in range(size - 1)]
        stacks.append(tuple(all_permutations[(size - 1) * stack_size:]))
    else:
        stacks = None

    stack = comm.scatter(stacks, root=0)

    start_time = time.time()
    best_rank, best_path, best_distance = explore_tree(rank, cities, list(stack))
    end_time = time.time()

    results = comm.gather((best_rank, best_path, best_distance, end_time - start_time), root=0)

    if rank == 0:
        best_rank, best_path, best_distance, _ = min(results, key=lambda x: x[2])
        print(f"Shortest path: {tuple(list(best_path) + [best_path[0]])}") # print shortest path seq
        print(f"Shortest distance: {best_distance}")
        max_time = max(time_taken for _, _, _, time_taken in results)
        print(f"Total time taken: {1000*max_time:.5f} ms")

        for i, (_, _, _, time_taken) in enumerate(results): # print each processor time
            print(f"Process {i} time: {1000*time_taken:.5f} ms")

if __name__ == "__main__":
    main()
