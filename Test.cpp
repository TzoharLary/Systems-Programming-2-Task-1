#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    SUBCASE("Graph with three nodes and two edges forming a cycle") {
       vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

    SUBCASE("Graph with five nodes and a disconnected component") {
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }
           
    SUBCASE("Graph with one node") {
        vector<vector<int>> graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

    SUBCASE("Graph with two unconnected nodes") {
        vector<vector<int>> graph = {
            {0, 0},
            {0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }

    SUBCASE("Connected graph") {
        vector<vector<int>> graph = {
            {0, 1},
            {1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

    SUBCASE("Disconnected graph") {
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }
    SUBCASE("Directed graph with two nodes and one edge") {
        vector<vector<int>> graph = {
            {0, 1},
            {0, 0}};
        g.loadGraph(graph);
        // g.printGraph();
        CHECK(ariel::Algorithms::isConnected(g) == false); // The graph is not connected because there's no path from node 1 to node 0
     }

    SUBCASE("Undirected graph with two nodes and one edge") {
        vector<vector<int>> graph = {
            {0, 1},
            {1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true); // The graph is connected because there's a path between every pair of nodes
    }

    SUBCASE("Directed graph with three nodes and two edges forming a cycle") {
        vector<vector<int>> graph = {
            {0, 1, 1},
            {0, 0, 1},
            {1, 0, 0}};
        g.loadGraph(graph);
        // g.printGraph();
        CHECK(ariel::Algorithms::isConnected(g) == true); // The graph is connected because there's a path between every pair of nodes
    }

    SUBCASE("Directed graph with three nodes and two edges not forming a cycle") {
         vector<vector<int>> graph = {
            {0, 1, 0},
            {0, 0, 1},
            {0, 0, 0}};
        g.loadGraph(graph);
        // g.printGraph();
        CHECK(ariel::Algorithms::isConnected(g) == false); // The graph is not connected because there's no path from node 2 to node 0 or node 1
    }
   
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    SUBCASE("Graph with three nodes and two edges forming a cycle") {
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    }
   SUBCASE("Graph with five nodes and a disconnected component") {
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
    }
   
    SUBCASE("Empty graph") {
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 1));
    }
   

    SUBCASE("Single node graph") {
        vector<vector<int>> graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "0");
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 1));
    }

    SUBCASE("Two nodes with no edge") {
        vector<vector<int>> graph = {{0, 0}, {0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "-1");
    }

    SUBCASE("Two nodes with an edge") {
        vector<vector<int>> graph = {{0, 1}, {1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");
    }

    SUBCASE("Three nodes in a line") {
        vector<vector<int>> graph = {{0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    }

    SUBCASE("Three nodes in a cycle") {
        vector<vector<int>> graph = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
    }
}

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph;

    SUBCASE("Test with a graph that contains a cycle of length 3") {
        graph = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
    }

    SUBCASE("Test with a graph that is not bipartite") {
        graph = {{0, 1, 1, 0, 0}, {1, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "0");
    }

    SUBCASE("Test with a graph that is bipartite and contains weights") {
        graph = {{0, 1, 0, 0, 0}, {1, 0, 3, 0, 0}, {0, 3, 0, 4, 0}, {0, 0, 4, 0, 5}, {0, 0, 0, 5, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
    }

    SUBCASE("Test with an empty graph") {
      CHECK_THROWS_WITH(g.loadGraph(graph), "Graph is empty");
    }

    SUBCASE("Test with a graph that only contains one node") {
        graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={}");
    }

    SUBCASE("Test with a graph that contains a cycle of length 2 and contains two nodes and one edge") {
        graph = {{0, 1}, {1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={1}");
    }

    SUBCASE("Test with a graph that contains two nodes but no edges") {
        graph = {{0, 0}, {0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={1}");
    }

    SUBCASE("Test with a graph that contains multiple disconnected components") {
        graph = {{0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
    }
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;

    SUBCASE("Graph with three nodes and two edges forming a cycle") {
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g) == false);
    }

    SUBCASE("Graph with five nodes and a disconnected component") {
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isContainsCycle(g) == true);
    }

    SUBCASE("Graph with no edges") {
        vector<vector<int>> graph = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        g.loadGraph(graph);
        CHECK_FALSE(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with a single edge") {
        vector<vector<int>> graph = {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}};
        g.loadGraph(graph);
        CHECK_FALSE(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with a self-loop") {
        vector<vector<int>> graph = {{0, 1, 0}, {0, 0, 0}, {0, 0, 1}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with a cycle") {
        vector<vector<int>> graph = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with no cycle") {
        vector<vector<int>> graph = {{0, 1, 0}, {1, 0, 0}, {0, 0, 0}};
        g.loadGraph(graph);
        CHECK_FALSE(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with multiple cycles") {
        vector<vector<int>> graph = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with multiple cycles and self-loops") {
        vector<vector<int>> graph = {{0, 1, 1}, {1, 0, 1}, {1, 1, 1}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }
    
    SUBCASE("Weighted graph with a cycle") {
        vector<vector<int>> graph = {{0, 1, 2}, {1, 0, 3}, {2, 3, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Weighted graph with no cycle") {
        vector<vector<int>> graph = {{0, 1, 0}, {1, 0, 2}, {0, 2, 0}};
        g.loadGraph(graph);
        CHECK_FALSE(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Weighted graph with multiple cycles") {
        vector<vector<int>> graph = {{0, 2, 3}, {2, 0, 1}, {3, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Weighted graph with multiple cycles and self-loops") {
        vector<vector<int>> graph = {{1, 2, 3}, {2, 1, 4}, {3, 4, 1}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

}


TEST_CASE("Test shortestPath with negative edge but no negative cycle")
{
    ariel::Graph grp;
    vector<vector<int>> graph = {
            {0, -1, 0, 0, 0},
            {-1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}
            };
    grp.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(grp, 0, 4) == "0->1->2->3->4");
}

TEST_CASE("Test shortestPath with negative edge but no negative cycle and directed graph")
{
    ariel::Graph grp;
    vector<vector<int>> graph = {
            {0, -1, 0, 0, 0},
            {0, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    grp.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(grp, 0, 4) == "0->1->2->3->4");
}

TEST_CASE("Test shortestPath with negative cycle")
{
    ariel::Graph grp;
    vector<vector<int>> graph = {
            {0, 1, -1, 0, 0},
            {1, 0, -3, 0, 0},
            {-1, -3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}
            };
    grp.loadGraph(graph);
    CHECK_THROWS(ariel::Algorithms::shortestPath(grp, 0, 4));
}

TEST_CASE("Test shortestPath with negative cycle and directed graph")
{
    ariel::Graph grp;
    vector<vector<int>> graph = {
            {0, 1, -1, 0, 0},
            {0, 0, -3, 0, 0},
            {-1, -3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}
            };
    grp.loadGraph(graph);
    CHECK_THROWS(ariel::Algorithms::shortestPath(grp, 0, 4));
}

TEST_CASE("Test shortestPath with disconnected graph")
{
    ariel::Graph grp;
    vector<vector<int>> graph = {
            {0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    grp.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(grp, 0, 3) == "-1");
}

TEST_CASE("Test negativeCycle")
{
    ariel::Graph g;

    // SUBCASE("Graph with no edges") {
    //     vector<vector<int>> graph = {
    //         {0, 0, 0}, 
    //         {0, 0, 0},
    //          {0, 0, 0}
    //          };
    //     g.loadGraph(graph);   
    //     // g.printGraph();
    //     CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNo negative cycle detected in directed graph.");
    // }

    // SUBCASE("Graph with positive weights") {
    //     vector<vector<int>> graph = {
    //         {0, 1, 2}, 
    //         {1, 0, 3}, 
    //         {2, 3, 0}
    //         };
    //     g.loadGraph(graph);
    //     // g.printGraph();
    //     CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNo negative cycle detected in directed graph.");
    // }

    // SUBCASE("Graph with negative weights but no negative cycle") {
    //     vector<vector<int>> graph = {
    //         {0, -1, 2},
    //          {-1, 0, 3},
    //           {2, 3, 0}
    //           };
    //     g.loadGraph(graph);
    //     g.printGraph();
    //     cout << ariel::Algorithms::negativeCycle(g) << endl;
    //     // the graph is not connected, so there is no negative cycle
    //     CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.");
    // }

    // SUBCASE("Graph with a negative cycle 1") {
    //     vector<vector<int>> graph = {
    //         {0, -1, 2}, 
    //         {-1, 0, -3}, 
    //         {2, -3, 0}
    //         };
    //     g.loadGraph(graph);     
    //     g.printGraph();
    //     cout << ariel::Algorithms::negativeCycle(g) << endl;
    //     CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.");
    // }

    // SUBCASE("Graph with a negative cycle 2") {
    //     vector<vector<int>> graph = {
    //         {0, 1, 2}, 
    //         {1, 0, -3},
    //         {2, -3, 0}};
    //     g.loadGraph(graph);        
    //     g.printGraph();
    //     // cout << ariel::Algorithms::negativeCycle(g) << endl;
    //     CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.");
    // }

    // SUBCASE("Graph with a negative cycle 3") {
    //         vector<vector<int>> graph = {
    //             {0, 1,-3}, 
    //             {1, 0, 2},
    //             {-3, 2, 0}};
    //         g.loadGraph(graph);        
    //         g.printGraph();
    //         // cout << ariel::Algorithms::negativeCycle(g) << endl;
    //         CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.");
    //     }

   

   
}







TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    SUBCASE("Empty graph1") {
        vector<vector<int>> graph = {{}};
      CHECK_THROWS_WITH(g.loadGraph(graph), "Graph is empty");
    }
    SUBCASE("Empty graph2") {
        vector<vector<int>> graph;
           CHECK_THROWS_WITH(g.loadGraph(graph), "Graph is empty");
    }
    SUBCASE("Empty graph3") {
    CHECK_THROWS_WITH(ariel::Algorithms::isConnected(g), "The graph is empty");
    }

}

