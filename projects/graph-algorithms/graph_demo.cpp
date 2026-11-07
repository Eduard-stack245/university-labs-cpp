// Reads a graph from a file and prints its minimum spanning tree and the
// shortest paths from one vertex.   graph_demo [file] [source vertex, 1-based]
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Graph.hpp"

int main(int argc, char** argv)
{
    const char* file = argc > 1 ? argv[1] : "graph6.txt";
    std::ifstream in(file);
    if (!in) { std::cerr << "cannot open " << file << "\n"; return 1; }

    try {
        gx::Graph g = gx::Graph::fromMatrix(in);
        const int source = (argc > 2 ? std::atoi(argv[2]) : 1) - 1;

        gx::Graph::MstResult mst = g.primMst();
        std::cout << "Minimum spanning tree (Prim):\n";
        for (const auto& e : mst.edges)
            std::cout << "  " << e.from + 1 << " - " << e.to + 1 << "  (weight " << e.weight << ")\n";
        std::cout << "  total weight: " << mst.total << (mst.connected ? "" : "   (graph is NOT connected)") << "\n\n";

        gx::Graph::PathResult sp = g.dijkstra(source);
        std::cout << "Shortest paths from vertex " << source + 1 << " (Dijkstra):\n";
        for (int v = 0; v < g.size(); v++) {
            std::cout << "  to " << v + 1 << ": ";
            std::vector<int> path = gx::Graph::pathTo(sp, v, source);
            if (path.empty()) { std::cout << "unreachable\n"; continue; }
            std::cout << "length " << sp.dist[static_cast<std::size_t>(v)] << ", path";
            for (std::size_t i = 0; i < path.size(); i++) std::cout << (i ? " -> " : " ") << path[i] + 1;
            std::cout << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
