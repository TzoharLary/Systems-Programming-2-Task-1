#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector>
#include <string>

// we define here the class Algorithms because it's contain a lot of code.
namespace ariel {
    class Algorithms {
    public:
        static bool isConnected(const Graph& g);
        static std::string shortestPath(const Graph& g, int start, int end);
        static bool isContainsCycle(const Graph& g);
        static std::string isBipartite(const Graph& g);
        static std::string negativeCycle(const Graph& g);
        static bool isSymmetric(const Graph& g);
        static void dfs(const Graph& g, size_t node, std::vector<bool>& visited, size_t n);
        static bool bellmanFordUndirected(const Graph& g, std::vector<int>& dist); // Updated function
        static bool bellmanFordDirected(const Graph& g, std::vector<int>& dist); // Updated function
        static bool johnson(const Graph& g);

    
  
    };
}

#endif // ALGORITHMS_HPP
