// Mail: tzohary1234@gmail.com
// Author: Tzohar Lary


#include "Algorithms.hpp"
#include <queue>
#include <limits>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <sstream> 


using namespace std;
using namespace ariel;

string Algorithms::shortestPath(const Graph& g, int start, int end) {
    
    // Check if the graph is empty using the isEmpty method of the graph object.
    // If it is empty, throw an invalid_argument exception with a message indicating the graph is empty.
    if (g.isEmpty()) {
        throw invalid_argument("The graph is empty");
    }

    // Get the size of the adjacency matrix of the graph, which represents the number of vertices in the graph.
    int n = g.getAdjacencyMatrix().size();

    // Check if the size of the adjacency matrix is 0, which means the graph has no vertices.
    // If so, return a string indicating the graph is empty.
    if (n == 0) {
        return "this graph is empty";
    }

    // Check if the start and end nodes are valid
    if (start < 0 || start >= n || end < 0 || end >= n) {
        throw invalid_argument("Start or end node does not exist");
    }

    // Initialize distances and predecessors
    vector<int> dist(n, numeric_limits<int>::max());
    vector<int> prev(n, -1);

    // Set the distance to the start node as 0
    dist[start] = 0;

    // Relax edges up to n-1 times
    for (int i = 0; i < n - 1; i++) {
    relax(g, dist, prev);
    }
    
    // Check for negative-weight cycles
    if (hasNegativeCycle(g, dist)) {
        // if a negative cycle is detected, so we can't find the shortest path 
        // because we cannot find a reliable shortest path.
        throw runtime_error("Graph contains a negative-weight cycle");
    }

    // If the distance to the end node is still infinity, no path exists
    if (dist[end] == numeric_limits<int>::max()) {
        return "-1"; // No path found
    }

        // Reconstruct path from end to start using the predecessor array
    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end()); // Reverse to get the correct order from start to end

    // Convert path to string format
    string pathStr = "";
    for (size_t i = 0; i < path.size(); ++i) {
        pathStr += to_string(path[i]);
        if (i < path.size() - 1) {
            pathStr += "->"; // Add arrow between nodes
        }
    }
    return pathStr; // Return the path as a string
}

bool Algorithms::isContainsCycle(const Graph& g) {
    // The purpose of the method is to check whether the graph g has a cycle.
    // It returns true if there is a cycle and false otherwise.

    int n = g.getAdjacencyMatrix().size();
    vector<bool> visited(n, false); // Array to store visited nodes
    vector<int> parent(n, -1); // Array to store parent nodes for find back edge

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            // if the dfsCycleCheck method returns true, then the graph has a cycle.
            if (dfsCycleCheck(g, i, visited, parent)) {
                return true;
            }
        }
    }
    // else, the graph does not have a cycle.
    return false;
}

std::string Algorithms::isBipartite(const Graph& g) {
    //BFS succeeds in coloring a two-color graph if and only if the graph is bipartite.

    // Check if the graph is empty using the isEmpty method of the graph object.
    if (g.isEmpty()) {
        return "this graph is empty";
    }
    int n = g.getAdjacencyMatrix().size();
    if (n == 0) {
        return "this graph is empty";
    }

    // Use -1 for uncolored, 0 and 1 for the two colors
    std::vector<int> colors(n, -1);
    for (int start = 0; start < n; ++start) {
        // Perform BFS from each uncolored vertex
        if (colors[start] == -1) {
        bool hasEdges = false;
        // Check if the current vertex has any edges
            for (int i = 0; i < n; ++i) {
                if (g.getAdjacencyMatrix()[start][i]) {
                    hasEdges = true;
                    break;
                }
            }
        
            if (!hasEdges) {
                // Handle the case where there are no edges.
                colors[start] = start % 2;  // Assign color based on vertex index

            }
            else {
            // Initialize BFS queue
            std::queue<int> q;
            //  Start BFS from the current vertex
            q.push(start);
            colors[start] = 0;  // Assign initial color

            // Perform BFS traversal
            while (!q.empty()) {
                //  Get the front of the queue  
                int node = q.front();
                q.pop();

                //  Traverse all adjacent vertices of the current vertex
                for (int i = 0; i < n; ++i) {
                    //  Check if there is an edge from the current vertex to vertex i
                    if (g.getAdjacencyMatrix()[node][i]) {  
                        
                        if (colors[i] == -1) {
                            colors[i] = 1 - colors[node];  // Assign opposite color
                            q.push(i);
                        } else if (colors[i] == colors[node]) {
                            return "0";  // Early odd cycle detection
                        }
                    }
                    
                }
            }
            }
        }
    }

    // Construct result string if the graph is bipartite
    std::string setA_str = "A={";
    std::string setB_str = "B={";
    for (int i = 0; i < n; ++i) {
        if (colors[i] == 0) {
            setA_str += std::to_string(i);
            setA_str += ", ";
        } else {
            setB_str += std::to_string(i);
            setB_str += ", ";
        }
    }
        // Remove trailing comma and space only if they exist
        if (setA_str.size() > 3) {
            setA_str.pop_back();
            setA_str.pop_back();
        }
        setA_str += "}";

        if (setB_str.size() > 3) {
            setB_str.pop_back();
            setB_str.pop_back();
        }
        setB_str += "}";


    return "The graph is bipartite: " + setA_str + ", " + setB_str;
}

bool Algorithms::isDirected(const Graph& g) {
    const auto& matrix = g.getAdjacencyMatrix();
    size_t n = matrix.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                return true;
            }
        }
    }

    return false;
}

string Algorithms::negativeCycle(const Graph& originalGraph) {
    int n = originalGraph.getAdjacencyMatrix().size();
    vector<int> baseDist(n, numeric_limits<int>::max()); // base distances array
    string result;

    if (!isDirected(originalGraph)) {
            vector<int> dist = baseDist; // create a copy of the base distances
            dist[2] = 0; // define the current node as the source
            bool negativeCycle = bellmanFord(originalGraph, dist);
            if (negativeCycle) {
                result = "Negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.";
                return result;
            } else {
                result = "No negative cycle detected in undirected graph.\n";
                if (hasNegativeEdge(originalGraph, dist)) {
                    result += "Negative cycle detected in directed graph.";
                } else {
                    result += "No negative cycle detected in directed graph.";
                }  
            }
        
    } else {
        result += "The graph cannot be interpreted as undirected.\n";
        for (int i = 0; i < n; ++i) {
            vector<int> dist = baseDist; // create a copy of the base distances
            dist[i] = 0; // define the current node as the source
            bool negativeCycle = bellmanFord(originalGraph, dist);
            if (negativeCycle) {
                result += "Negative cycle detected in the graph.";
                // cout << result << endl;
                return result;
            }
        }
        result += "No negative cycle detected in the graph.";
    }
    
    // cout << result << endl;
    return result;
}

bool Algorithms::bellmanFord(const Graph& g, vector<int>& dist) {
    int n = g.getAdjacencyMatrix().size();
    vector<int> parent(n, -1);
    
    // Relax edges up to n-1 times
    for (int i = 0; i < n - 1; ++i) {
        // cout << "starting relax number " << i << endl;
        relax(g, dist, parent);
    }

    // Check for negative cycles
    return hasNegativeCycle(g, dist);
}

bool Algorithms::hasNegativeEdge(const Graph& g, vector<int>& dist) {
    auto adjMatrix = g.getAdjacencyMatrix();  // retrieve the adjacency matrix of the graph
    for (int i = 0; i < adjMatrix.size(); ++i) {
        for (int j = 0; j < adjMatrix[i].size(); ++j) {
            if (adjMatrix[i][j] < 0) {
                return true; // found a negative edge in the graph return true
            }
        }
    }
    return false; // no negative edges found in the graph return false
}
    
bool Algorithms::hasNegativeCycle(const Graph& g, const vector<int>& dist) {
    int n = g.getAdjacencyMatrix().size();
    const vector<vector<int>>& adj = g.getAdjacencyMatrix();
    vector<bool> calculated(n, false); // New array to keep track of calculated nodes
    for (int u = 0; u < n; ++u) {
        // Skip nodes that are not connected to the main component
        if (dist[u] == numeric_limits<int>::max()) continue;
        const vector<int>& neighbors = adj[u];
        for (int v = 0; v < n-1; ++v) {
            // Check if there is an edge and if the edge can further decrease the distance
            if (neighbors[v] != 0 && dist[u] != numeric_limits<int>::max() && dist[v] > dist[u] + neighbors[v] && !calculated[v]) {
                return true;
            }
        }
        calculated[u] = true; // Mark the node as calculated after checking all its neighbors
    }
    return false;
}

void Algorithms::relax(const Graph& g, vector<int>& dist, vector<int>& parent) {
    const vector<vector<int>>& adj = g.getAdjacencyMatrix();
    int n = adj.size();
    for (int u = 0; u < n; ++u) {
        if (dist[u] == numeric_limits<int>::max()) continue;
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] != 0 ) {
                if (isDirected(g)) {
                    if (dist[v] > dist[u] + adj[u][v]) {
                        dist[v] = dist[u] + adj[u][v];
                        parent[v] = u;
                    }
                } else {
                    if (dist[v] > dist[u] + adj[u][v] && parent[u] != v) {
                        dist[v] = dist[u] + adj[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }
    
}

bool Algorithms::isConnected(const Graph& g) {
    if (g.isEmpty()) {
        throw invalid_argument("The graph is empty");
    }
    size_t n = g.getAdjacencyMatrix().size(); // Number of vertices in the graph
    if (n == 0) {
        throw invalid_argument("The graph is empty");
    }
    for (size_t startNode = 0; startNode < n; ++startNode) {
        vector<bool> visited(n, false);
        dfs(g, startNode, visited,n);
        for (bool nodeVisited : visited) {
            if (!nodeVisited) {
                return false;
            }
        }
    }
    return true;
}

void Algorithms::dfs(const Graph& g, size_t node, vector<bool>& visited, size_t n) {
    visited[node] = true;
    for (size_t i = 0; i < n; ++i) {
        if (g.getAdjacencyMatrix()[node][i] != 0 && !visited[i]) {
            dfs(g, i, visited,n);
        }
    }
}

bool Algorithms::dfsCycleCheck(const Graph& g, int v, vector<bool>& visited, vector<int>& parent) {
    int n = g.getAdjacencyMatrix().size();
    if (visited[v]) {
        // Check for back edge (directed cycle)
        if (parent[v] != -1 && g.getAdjacencyMatrix()[parent[v]][v] != 0) {
            return true;
        }

        // Check for self-loop (directed cycle)
        if (g.getAdjacencyMatrix()[v][v] != 0) {
            return true;
        }
    }

    visited[v] = true;
    for (int i = 0; i < n; ++i) {
        // if there is an edge from the current node to node i - the adjacent node
        if (g.getAdjacencyMatrix()[v][i] != 0) {
            // if the adjacent node is not visited - mean that he is still white, so we need to visit him
            if (!visited[i]) {
                parent[i] = v;
                if (dfsCycleCheck(g, i, visited, parent)) {
                    return true;
                }
            }
            // check again if there is a back edge to the parent node
            else if (parent[v] != i && g.getAdjacencyMatrix()[i][v] != 0) { // Weighted graph handling
                return true; // Found a cycle
            }
        }
    }
    visited[v] = false; // Unmark the current node as visited
    return false;
}
