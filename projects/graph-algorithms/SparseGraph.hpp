#pragma once
// ---------------------------------------------------------------------------
// The same two problems as Graph.hpp, but for big sparse graphs:
//   * the graph is stored as adjacency lists (memory O(V + E) instead of O(V^2))
//   * Dijkstra uses a priority queue:  O((V + E) log V)  instead of O(V^2)
//   * the spanning tree is built with Kruskal's algorithm (sort the edges + union-find): O(E log E)
// Results use the same types as Graph (Graph::PathResult, Graph::MstResult), so the two classes can be compared.
// ---------------------------------------------------------------------------
#include <algorithm>
#include <numeric>
#include <queue>
#include <utility>
#include "Graph.hpp"

namespace gx {

class SparseGraph
{
public:
    using Weight = Graph::Weight;

    explicit SparseGraph(int vertices = 0) : adj_(static_cast<std::size_t>(vertices < 0 ? 0 : vertices))
    {
        if (vertices < 0) throw std::invalid_argument("negative number of vertices");
    }

    // Copies all edges of a matrix graph.
    static SparseGraph fromGraph(const Graph& g)
    {
        SparseGraph s(g.size());
        for (int i = 0; i < g.size(); i++)
            for (int j = i + 1; j < g.size(); j++)
                if (g.weight(i, j)) s.addEdge(i, j, g.weight(i, j));
        return s;
    }

    int size() const { return static_cast<int>(adj_.size()); }
    std::size_t edgeCount() const { return edges_.size(); }

    // Adds an undirected edge. Weight must be > 0. Parallel edges are allowed (the cheapest one wins in the algorithms).
    void addEdge(int a, int b, Weight weight)
    {
        check(a); check(b);
        if (a == b) throw std::invalid_argument("loops are not supported");
        if (weight == 0) throw std::invalid_argument("edge weight must be positive");
        adj_[idx(a)].push_back({b, weight});
        adj_[idx(b)].push_back({a, weight});
        edges_.push_back({a, b, weight});
    }

    // Dijkstra with a priority queue. dist[v] == Graph::INF if v is unreachable.
    Graph::PathResult dijkstra(int source) const
    {
        check(source);
        Graph::PathResult r;
        r.dist.assign(adj_.size(), Graph::INF);
        r.parent.assign(adj_.size(), -1);
        using Item = std::pair<unsigned long long, int>;
        std::priority_queue<Item, std::vector<Item>, std::greater<Item>> queue;
        r.dist[idx(source)] = 0;
        queue.push({0, source});
        while (!queue.empty()) {
            const Item top = queue.top();
            queue.pop();
            const int u = top.second;
            if (top.first != r.dist[idx(u)]) continue;                 // outdated queue entry
            for (const auto& edge : adj_[idx(u)]) {
                const unsigned long long candidate = top.first + edge.second;
                if (candidate < r.dist[idx(edge.first)]) { r.dist[idx(edge.first)] = candidate; r.parent[idx(edge.first)] = u; queue.push({candidate, edge.first}); }
            }
        }
        return r;
    }

    // Kruskal's algorithm. For a graph that is not connected it returns the spanning FOREST and `connected` is false.
    Graph::MstResult kruskalMst() const
    {
        std::vector<Graph::Edge> sorted = edges_;
        std::stable_sort(sorted.begin(), sorted.end(), [](const Graph::Edge& a, const Graph::Edge& b) { return a.weight < b.weight; });
        std::vector<int> parent(adj_.size());
        std::iota(parent.begin(), parent.end(), 0);
        Graph::MstResult r;
        for (const Graph::Edge& e : sorted) {
            const int a = root(parent, e.from), b = root(parent, e.to);
            if (a == b) continue;
            parent[idx(a)] = b;
            r.edges.push_back(e);
            r.total += e.weight;
        }
        r.connected = adj_.empty() || r.edges.size() + 1 == adj_.size();
        return r;
    }

private:
    static std::size_t idx(int v) { return static_cast<std::size_t>(v); }
    void check(int v) const { if (v < 0 || v >= size()) throw std::out_of_range("vertex index out of range"); }
    static int root(std::vector<int>& parent, int x)
    {
        while (parent[idx(x)] != x) { parent[idx(x)] = parent[idx(parent[idx(x)])]; x = parent[idx(x)]; }   // path halving
        return x;
    }

    std::vector<std::vector<std::pair<int, Weight>>> adj_;     // (neighbour, weight)
    std::vector<Graph::Edge> edges_;
};

} // namespace gx
