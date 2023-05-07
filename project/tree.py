import numpy as np
from mpi4py import MPI
from itertools import permutations

""" This script implements the static tree search using MPI library of python for parallel computing.
    Documentation used for this code: https://mpi4py.readthedocs.io/en/stable/
    The inputs are the number of cities (n) and randomly generated coordinates of the cities.
    The outputs are the shortest path and the time taken (ms) to find the shortest path.
    The process0 (root node) chunks the data to other process and at the end collect the results from other processes.

    To run this script, use the following command at MPI terminal:
    mpiexec -n 4 python tree.py

    The number of processes can be changed by changing the value of -n 
    The -n values I tried: [1,2,4,8,16]

    Note that every run will give different results because the cities are randomly generated.
"""

# Function to calculate the distance between two cities
def distance(city1, city2):
    return np.linalg.norm(city1 - city2)

# Function to calculate the total distance of a path
def path_distance(path, cities):
    return sum([distance(cities[path[i]], cities[path[i+1]]) for i in range(len(path)-1)])

# Function to split data into chunks
def split_data(data, num_chunks):
    chunk_size = len(data) // num_chunks
    remainder = len(data) % num_chunks
    chunks = []
    start = 0
    for i in range(num_chunks):
        end = start + chunk_size + (1 if i < remainder else 0)
        chunks.append(data[start:end])
        start = end
    return chunks

# Function to perform a tree search for the shortest path
def tree_search(cities):
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank() #rank of the process
    size = comm.Get_size() #number of processes

    if rank == 0:
        paths = list(permutations(range(1, len(cities))))
        paths = [tuple([0] + list(path) + [0]) for path in paths]
        # print("List paths:", paths) #List of tuples (all possible paths)
        print("Number of paths:", len(paths)) #Number of paths
        print("Number of processes:", size)
        chunks = split_data(paths, size)
    else:
        chunks = None

    local_paths = comm.scatter(chunks, root=0) # distribute chunks to all other processes
    print("Rank:", rank, "Local paths:", local_paths)
    local_shortest_distance = float('inf')
    local_shortest_path = None

    for path in local_paths:
        dist = path_distance(path, cities) 
        if dist < local_shortest_distance:
            local_shortest_distance = dist
            local_shortest_path = path

    shortest_distance = comm.allreduce(local_shortest_distance, op=MPI.MIN) # reduce dist accross all processes, 
                                                                            # the result is returned to all processes
    shortest_path = comm.bcast(local_shortest_path, root=0) # root process broadcasts the shortest path to all processes

    return shortest_path, shortest_distance

if __name__ == '__main__':
    # Generate some random cities
    num_cities = 8
    cities = np.random.rand(num_cities, 2)

    # Perform a tree search for the shortest path using MPI
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    if rank == 0:
        start_time = MPI.Wtime()
    shortest_path, shortest_distance = tree_search(cities)
    if rank == 0:
        end_time = MPI.Wtime()

        # Print the results and time taken
        print(f"Shortest path: {shortest_path}")
        print(f"Shortest distance: {shortest_distance}")
        print(f"Time taken: {1000*(end_time - start_time):.4f} ms")
