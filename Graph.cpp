// Mail: tzohary1234@gmail.com
// Author: Tzohar Lary
       
#include "Graph.hpp"

using namespace std;
using namespace ariel;

void Graph::loadGraph(const vector<vector<int>>& matrix) {
     if (matrix.empty() || (matrix.size() == 1 && matrix[0].empty())) {
        throw invalid_argument("Graph is empty");
    }
    size_t size = matrix.size();
    for (const auto& row : matrix) {
        if (row.empty() || row.size() != size) {
            throw invalid_argument("Matrix must be square and non-empty");
        }
    }
    adjacencyMatrix = matrix;
}
bool Graph::isEmpty() const {
    return adjacencyMatrix.empty();
}
void Graph::addNode() {
    int n = adjacencyMatrix.size();
    vector<int> newRow(n + 1, 0);
    adjacencyMatrix.push_back(newRow);
    for (auto& row : adjacencyMatrix) {
        row.push_back(0);
    }
}

void Graph::removeNode() {
    if (!adjacencyMatrix.empty()) {
        adjacencyMatrix.pop_back();
        for (auto& row : adjacencyMatrix) {
            row.pop_back();
        }
    }
}

void Graph::setEdge(int i, int j, int val) {
    if (i < 0 || i >= adjacencyMatrix.size() || j < 0 || j >= adjacencyMatrix.size()) {
        throw out_of_range("Index out of range");
    }
    adjacencyMatrix[i][j] = val;
}

const vector<vector<int>>& Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

void Graph::printGraph() const {
    for (const auto& row : adjacencyMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}
