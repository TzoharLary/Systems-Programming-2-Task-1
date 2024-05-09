#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

namespace ariel {
        class Graph {
            private:
                std::vector<std::vector<int>> adjacencyMatrix;

            public:
                void loadGraph(const std::vector<std::vector<int>>& matrix);
                const std::vector<std::vector<int>>& getAdjacencyMatrix() const;
                void printGraph() const;
                bool isEmpty() const;
                void addNode();
                void removeNode();
                void setEdge(int i, int j, int val);

        };
}

#endif // GRAPH_HPP
