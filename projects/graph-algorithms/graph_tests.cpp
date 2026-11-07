// Self-checking tests: Prim is compared with Kruskal, Dijkstra with Floyd-Warshall,
// on the lab graph and on many random graphs. Exit code 0 = everything is correct.
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include "Graph.hpp"

using gx::Graph;
static int failures = 0;
static void check(bool ok, const std::string& what) { if (!ok) { failures++; std::cout << "FAIL: " << what << "\n"; } }

static int findRoot(std::vector<int>& p, int x) { return p[x] == x ? x : p[x] = findRoot(p, p[x]); }

static unsigned long long kruskal(const Graph& g, bool& connected)
{
    std::vector<Graph::Edge> edges;
    for (int i = 0; i < g.size(); i++) for (int j = i + 1; j < g.size(); j++) if (g.weight(i, j)) edges.push_back({i, j, g.weight(i, j)});
    std::sort(edges.begin(), edges.end(), [](const Graph::Edge& a, const Graph::Edge& b) { return a.weight < b.weight; });
    std::vector<int> p(g.size()); std::iota(p.begin(), p.end(), 0);
    unsigned long long total = 0; int used = 0;
    for (const auto& e : edges) { int a = findRoot(p, e.from), b = findRoot(p, e.to); if (a != b) { p[a] = b; total += e.weight; used++; } }
    connected = (used == std::max(0, g.size() - 1));
    return total;
}

static std::vector<std::vector<unsigned long long>> floyd(const Graph& g)
{
    const unsigned long long INF = Graph::INF / 4;
    std::vector<std::vector<unsigned long long>> d(g.size(), std::vector<unsigned long long>(g.size(), INF));
    for (int i = 0; i < g.size(); i++) { d[i][i] = 0; for (int j = 0; j < g.size(); j++) if (g.weight(i, j)) d[i][j] = g.weight(i, j); }
    for (int k = 0; k < g.size(); k++) for (int i = 0; i < g.size(); i++) for (int j = 0; j < g.size(); j++) d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
    return d;
}

static void compareWithReferences(const Graph& g, const std::string& label)
{
    bool conn = true;
    const unsigned long long ref = kruskal(g, conn);
    Graph::MstResult mst = g.primMst();
    check(mst.connected == conn, label + ": connectivity");
    check(!conn || mst.total == ref, label + ": MST weight " + std::to_string(mst.total) + " vs Kruskal " + std::to_string(ref));
    check(!conn || mst.edges.size() == static_cast<std::size_t>(std::max(0, g.size() - 1)), label + ": MST edge count");

    const auto fw = floyd(g);
    for (int s = 0; s < g.size(); s++) {
        Graph::PathResult r = g.dijkstra(s);
        for (int t = 0; t < g.size(); t++) {
            const unsigned long long want = fw[s][t] >= Graph::INF / 4 ? Graph::INF : fw[s][t];
            check(r.dist[t] == want, label + ": dist " + std::to_string(s) + "->" + std::to_string(t));
        }
    }
}

int main()
{
    // 1) the lab graph, with hand-computed answers
    std::istringstream lab("6\n0 5 0 1 3 0\n5 0 1 0 7 0\n0 1 0 0 5 4\n1 0 0 0 2 0\n3 7 5 2 0 10\n0 0 4 0 10 0\n");
    Graph g = Graph::fromMatrix(lab);
    check(g.primMst().total == 13, "lab graph: MST weight is 13");
    Graph::PathResult r = g.dijkstra(0);
    check(r.dist[5] == 10, "lab graph: shortest 1 -> 6 is 10");
    std::vector<int> path = Graph::pathTo(r, 5, 0);
    check(path == std::vector<int>({0, 1, 2, 5}), "lab graph: path 1-2-3-6");
    compareWithReferences(g, "lab graph");

    // 2) random graphs, connected and not
    std::mt19937 rng(2026);
    for (int rep = 0; rep < 300; rep++) {
        const int n = 1 + static_cast<int>(rng() % 25);
        Graph h(n);
        const int density = 10 + static_cast<int>(rng() % 70);       // percent of possible edges
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (static_cast<int>(rng() % 100) < density) h.setEdge(i, j, 1 + rng() % 20);
        compareWithReferences(h, "random #" + std::to_string(rep));
    }

    // 3) input validation
    auto throws = [](const std::string& text) { std::istringstream s(text); try { Graph::fromMatrix(s); } catch (const std::exception&) { return true; } return false; };
    check(throws("2\n0 1\n2 0\n"), "asymmetric matrix is rejected");
    check(throws("2\n1 0\n0 0\n"), "non-zero diagonal is rejected");
    check(throws("3\n0 1\n"), "incomplete matrix is rejected");
    check(Graph(0).primMst().edges.empty(), "empty graph");

    std::cout << (failures ? "graph tests FAILED\n" : "graph tests passed\n");
    return failures ? 1 : 0;
}
