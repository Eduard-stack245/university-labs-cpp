// Self-checking tests for SparseGraph: the results must match the matrix versions (Prim / Dijkstra)
// on many random graphs. Exit code 0 = everything is correct.
#include <iostream>
#include <random>
#include <string>
#include "SparseGraph.hpp"

using gx::Graph;
using gx::SparseGraph;
static int failures = 0;
static void check(bool ok, const std::string& what) { if (!ok) { failures++; std::cout << "FAIL: " << what << "\n"; } }
template <class F> static bool throwsError(F f) { try { f(); } catch (const std::exception&) { return true; } return false; }

int main()
{
    std::mt19937 rng(77);
    for (int rep = 0; rep < 300; rep++) {
        const int n = 1 + static_cast<int>(rng() % 30);
        Graph g(n);
        const int density = 5 + static_cast<int>(rng() % 80);
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (static_cast<int>(rng() % 100) < density) g.setEdge(i, j, 1 + rng() % 25);
        const SparseGraph s = SparseGraph::fromGraph(g);
        const std::string label = "random #" + std::to_string(rep);

        for (int src = 0; src < n; src++) {
            const Graph::PathResult a = g.dijkstra(src), b = s.dijkstra(src);
            check(a.dist == b.dist, label + ": Dijkstra distances from " + std::to_string(src));
            for (int t = 0; t < n; t++) {                                  // the parent chain must really add up to dist
                const std::vector<int> path = Graph::pathTo(b, t, src);
                unsigned long long sum = 0;
                for (std::size_t k = 1; k < path.size(); k++) sum += g.weight(path[k - 1], path[k]);
                check(b.dist[static_cast<std::size_t>(t)] == Graph::INF ? path.empty() : sum == b.dist[static_cast<std::size_t>(t)], label + ": path weight equals dist");
            }
        }
        const Graph::MstResult prim = g.primMst(), kruskal = s.kruskalMst();
        check(prim.connected == kruskal.connected, label + ": connectivity");
        if (prim.connected) check(prim.total == kruskal.total && kruskal.edges.size() == static_cast<std::size_t>(n - 1), label + ": MST weight Prim " + std::to_string(prim.total) + " vs Kruskal " + std::to_string(kruskal.total));
    }

    // parallel edges: the cheapest one is used
    SparseGraph p(2);
    p.addEdge(0, 1, 9); p.addEdge(0, 1, 4);
    check(p.dijkstra(0).dist[1] == 4 && p.kruskalMst().total == 4, "parallel edges: cheapest wins");

    // big sparse graph: a chain of 200000 vertices (the matrix version would need 160 GB)
    const int big = 200000;
    SparseGraph chain(big);
    for (int i = 0; i + 1 < big; i++) chain.addEdge(i, i + 1, 1 + static_cast<unsigned>(i % 7));
    unsigned long long expected = 0;
    for (int i = 0; i + 1 < big; i++) expected += 1 + static_cast<unsigned>(i % 7);
    check(chain.dijkstra(0).dist[big - 1] == expected, "200000-vertex chain: Dijkstra");
    check(chain.kruskalMst().total == expected && chain.kruskalMst().connected, "200000-vertex chain: Kruskal");

    // validation
    check(throwsError([] { SparseGraph(3).addEdge(0, 0, 1); }), "loops are rejected");
    check(throwsError([] { SparseGraph(3).addEdge(0, 1, 0); }), "zero weight is rejected");
    check(throwsError([] { SparseGraph(3).addEdge(0, 5, 1); }), "vertex out of range is rejected");
    check(throwsError([] { SparseGraph(-1); }), "negative size is rejected");
    check(SparseGraph(0).kruskalMst().connected, "empty graph");

    std::cout << (failures ? "sparse graph tests FAILED\n" : "sparse graph tests passed\n");
    return failures ? 1 : 0;
}
