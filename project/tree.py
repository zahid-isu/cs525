import numpy as np
from mpi4py import MPI
from itertools import permutations

"""Static tree search"""

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
    rank = comm.Get_rank()
    size = comm.Get_size()

    if rank == 0:
        paths = list(permutations(range(1, len(cities))))
        paths = [tuple([0] + list(path) + [0]) for path in paths]
        chunks = split_data(paths, size)
    else:
        chunks = None

    local_paths = comm.scatter(chunks, root=0)
    local_shortest_distance = float('inf')
    local_shortest_path = None

    for path in local_paths:
        dist = path_distance(path, cities)
        if dist < local_shortest_distance:
            local_shortest_distance = dist
            local_shortest_path = path

    shortest_distance = comm.allreduce(local_shortest_distance, op=MPI.MIN)
    shortest_path = comm.bcast(local_shortest_path, root=0)

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
