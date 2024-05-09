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
            if (g.isEmpty()) {
                throw invalid_argument("The graph is empty");
            }
            int n = g.getAdjacencyMatrix().size();
            if (n == 0) {
                return "this graph is empty";
            }

            // Check if the start and end nodes are valid
            if (start < 0 || start >= n || end < 0 || end >= n) {
                throw invalid_argument("Start or end node does not exist");
            }
            
            vector<int> dist(n, numeric_limits<int>::max());
            vector<int> prev(n, -1);

            dist[start] = 0;

            // Relax edges up to n-1 times
            for (int i = 0; i < n - 1; i++) {
                for (int u = 0; u < n; u++) {
                    for (int v = 0; v < n; v++) {
                        int weight = g.getAdjacencyMatrix()[u][v];
                        if (weight != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                            dist[v] = dist[u] + weight;
                            prev[v] = u;
                        }
                    }
                }
            }

            // Check for negative-weight cycles
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) {
                    int weight = g.getAdjacencyMatrix()[u][v];
                    if (weight != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                        return "Negative cycle detected";
                    }
                }
            }

            if (dist[end] == numeric_limits<int>::max()) {
                return "-1"; // No path found
            }

            // Reconstruct path
            vector<int> path;
            for (int at = end; at != -1; at = prev[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());

            string pathStr = "";
            for (size_t i = 0; i < path.size(); ++i) {
                pathStr += to_string(path[i]);
                if (i < path.size() - 1) {
                    pathStr += "->";
                }
            }

            return pathStr;
        }

        bool Algorithms::isContainsCycle(const Graph& g) {
            int n = g.getAdjacencyMatrix().size();
            vector<bool> visited(n, false);
            vector<int> parent(n, -1); // Array to store parent nodes

            function<bool(int)> dfs = [&](int v) {
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
                    if (g.getAdjacencyMatrix()[v][i] != 0) {
                        if (!visited[i]) {
                            parent[i] = v;
                            if (dfs(i)) {
                                return true;
                            }
                        } else if (parent[v] != i && g.getAdjacencyMatrix()[i][v] != 0) { // Weighted graph handling
                            return true; // Minimum weighted cycle
                        }
                    }
                }
                visited[v] = false; // Unmark the current node as visited
                return false;
            };

            for (int i = 0; i < n; ++i) {
                if (!visited[i]) {
                    if (dfs(i)) {
                        return true;
                    }
                }
            }
            return false;
        }

        std::string Algorithms::isBipartite(const Graph& g) {
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



        // string Algorithms::negativeCycle(const Graph& g) {
        //     int n = g.getAdjacencyMatrix().size();
        //     for (int start = 0; start < n; ++start) {
        //         vector<int> dist(n, numeric_limits<int>::max());
        //         dist[start] = 0;
        //        // Relax edges up to n-1 times
        //         for (int i = 0; i < n - 1; ++i) {
        //             for (int u = 0; u < n; ++u) {
        //                 for (int v = 0; v < n; ++v) {
        //                     if (g.getAdjacencyMatrix()[u][v] != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + g.getAdjacencyMatrix()[u][v] < dist[v]) {
        //                         dist[v] = dist[u] + g.getAdjacencyMatrix()[u][v];
        //                     }
        //                 }
        //             }
        //         }

        //         for (int u = 0; u < n; ++u) {
        //             for (int v = 0; v < n; ++v) {
        //                 if (g.getAdjacencyMatrix()[u][v] != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + g.getAdjacencyMatrix()[u][v] < dist[v]) {
        //                     return "Negative cycle detected";
        //                 }
        //             }
        //         }
        //     }

        //     return "No negative cycle";
        // }

        bool Algorithms::isSymmetric(const Graph& g) {

            const auto& matrix = g.getAdjacencyMatrix();
            size_t n = matrix.size();

            for (size_t i = 0; i < n; ++i) {
                for (size_t j = i + 1; j < n; ++j) {
                    if (matrix[i][j] != matrix[j][i]) {
                        return false;
                    }
                }
            }

            return true;
        }



        string Algorithms::negativeCycle(const Graph& g) {
            int n = g.getAdjacencyMatrix().size();
            vector<int> dist(n, numeric_limits<int>::max());
            dist[0] = 0; // assuming source vertex is 0
            string result;
            bool isDirect = !isSymmetric(g);
            // for undirected graph
            if (!isDirect){
                bool Negative_Cycle_Undirected = johnson(g);
                bool Negative_Cycle_directed = bellmanFordDirected(g, dist);
                // if negative cycle detected in undirected graph
                if (Negative_Cycle_Undirected)
                {
                    result = "Negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.";
                }
                // look on the graph like directed graph.
                else
                {
                    result = "No negative cycle detected in undirected graph.\n";
                    if (Negative_Cycle_directed)
                    {
                        result += "Negative cycle detected in directed graph.";
                    }
                    else
                    {
                        result += "No negative cycle detected in directed graph.";
                    }   
                }
            }
           
            else
            {
                result += "The graph cannot be interpreted as undirected.\n";
                bool Negative_Cycle_directed = bellmanFordDirected(g, dist);
                if (Negative_Cycle_directed)
                {
                    result += "Negative cycle detected in directed graph.";
                }
                else
                {
                    result += "No negative cycle detected in directed graph.";
                }
            }
            return result;
        }






        bool hasNegativeCycle(const std::vector<std::vector<int>>& graph) {
            int n = graph.getAdjacencyMatrix().size();
            std::vector<int> dist(n, std::numeric_limits<int>::max());
            dist[0] = 0;

            for (int i = 0; i < n - 1; ++i) {
                for (int u = 0; u < n; ++u) {
                    for (int v = 0; v < n; ++v) {
                        if (graph[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + graph[u][v] < dist[v]) {
                            dist[v] = dist[u] + graph[u][v];
                        }
                    }
                }
            }

            for (int u = 0; u < n; ++u) {
                for (int v = 0; v < n; ++v) {
                    if (graph[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + graph[u][v] < dist[v]) {
                        return true;
                    }
                }
            }

            return false;
        }    
          
          
          
          
          
            // cout << "1No negative cycle detected in undirected graph." << endl;







        bool Algorithms::bellmanFordDirected(const Graph& g, vector<int>& dist) {
            int n = g.getAdjacencyMatrix().size();
            // Relax edges up to n-1 times
            for (int i = 0; i < n - 1; ++i) {
                for (int u = 0; u < n; ++u) {
                    // Check to prevent unnecessary calculation
                    if (dist[u] == numeric_limits<int>::max()) continue;
                    const vector<int>& neighbors = g.getAdjacencyMatrix()[u];
                    for (int v = 0; v < n; ++v) {
                        // Update the distance to v according to the weight of the edge (u, v)
                        if (neighbors[v] != 0) {
                            dist[v] = min(dist[v], dist[u] + neighbors[v]);
                        }
                    }
                }
            }
            // Check for negative cycles
            for (int u = 0; u < n; ++u) {
                const vector<int>& neighbors = g.getAdjacencyMatrix()[u];
                for (int v = 0; v < n; ++v) {
                    if (neighbors[v] != 0 && dist[v] > dist[u] + neighbors[v]) {
                        return true;
                    }
                }
            }
            return false;
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





