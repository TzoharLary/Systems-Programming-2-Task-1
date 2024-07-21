# Systems Programming 2 - Task 1

## Author:
Tzohar Lary

## Email:
tzohary1234@gmail.com

## Project Description
This project deals with graph algorithms, including finding the shortest path, detecting negative cycles, and checking if a graph is bipartite.

## Installation and Running
To run the project, you need to use the clang++ compiler and run the following commands:

1. **Clone the Repository**: First, you need to clone the repository to your local machine. Open a terminal and run the following command:

    ```bash
    git clone https://github.com/TzoharLary/Systems-Programming-2-Task-1.git
    ```

2. **Navigate to the Project Directory**: Change your current directory to the project directory:

    ```bash
    cd Systems-Programming-2-Task-1
    ```

3. **Build the Project**: You can build the project using the `make` command:

    ```bash
    make
    ```

4. **Clean the Project**: If you want to clean the project (remove all the build files), you can use the following command:

    ```bash
    make clean
    ```
## Testing
The project includes 54 different test cases to verify the functionality of the algorithms, divided into 6 different types of test cases. To run the tests, use the following commands:

```bash
make test
./test
```
    
## Demo
To run the demo, use the following command in the terminal:

    ```bash
    make demo
    ```
## Main Functions in the Project

1. `string Algorithms::shortestPath(const Graph& g, int start, int end)`: This function calculates the shortest path between two nodes in a graph using the Bellman-Ford algorithm. If no path is found, it returns "-1".

2. `bool Algorithms::isContainsCycle(const Graph& g)`: This function checks if the graph contains a cycle using Depth-First Search (DFS).

3. `std::string Algorithms::isBipartite(const Graph& g)`: This function checks if the graph is bipartite and returns a string representing the two sets if it is.

4. `bool Algorithms::isDirected(const Graph& g)`: This function checks if the graph is directed by comparing the values in the adjacency matrix.

5. `string Algorithms::negativeCycle(const Graph& g)`: This function checks for a negative cycle in the graph using the Bellman-Ford algorithm. It uses the `hasNegativeEdge` function to determine if there are negative edges in the graph.

6. `bool Algorithms::bellmanFord(const Graph& g, vector<int>& dist)`: This function runs the Bellman-Ford algorithm on the graph and returns whether a negative cycle was found.

7. `bool Algorithms::hasNegativeEdge(const Graph& g, vector<int>& dist)`: This function checks if the graph contains any negative edges.

7. `bool Algorithms::hasNegativeCycle(const Graph& g, const vector<int>& dist)`: This function checks for a negative cycle in the graph after running the Bellman-Ford algorithm.

8. `void Algorithms::relax(const Graph& g, vector<int>& dist, vector<int>& parent)`: This function performs edge relaxation in the graph as part of the Bellman-Ford algorithm.

9. `bool Algorithms::isConnected(const Graph& g)`: This function checks if the graph is connected, meaning there is a path between every pair of nodes.

10. `void Algorithms::dfs(const Graph& g, size_t node, vector<bool>& visited, size_t n)`: This function performs Depth-First Search (DFS) on the graph to check connectivity.

The code uses several data structures like vectors and queues, and it also uses concepts like graph theory and algorithms like DFS (Depth-First Search) and the Bellman-Ford algorithm.
