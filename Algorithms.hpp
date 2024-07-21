// Mail: tzohary1234@gmail.com
// Author: Tzohar Lary
   

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector>
#include <string>
using namespace std;

// we define here the class Algorithms because it's contain a lot of code.
namespace ariel {
    class Algorithms {
    public:
        static bool isConnected(const Graph& g);
        static std::string shortestPath(const Graph& g, int start, int end);
        static bool isContainsCycle(const Graph& g);
        static std::string isBipartite(const Graph& g);
        static std::string negativeCycle(const Graph& g);
        static bool isDirected(const Graph& g);
        static void dfs(const Graph& g, size_t node, std::vector<bool>& visited, size_t n);
        static bool dfsCycleCheck(const Graph& g, int v, vector<bool>& visited, vector<int>& parent);
        static bool bellmanFord(const Graph& g, std::vector<int>& dist); // Updated function
        static bool hasNegativeEdge(const Graph& g, std::vector<int>& dist); // Updated function
        static void relax(const Graph& g, vector<int>& dist, vector<int>& parent);
        static bool hasNegativeCycle(const Graph& g, const vector<int>& dist);  

    
  
    };
}

#endif // ALGORITHMS_HPP
