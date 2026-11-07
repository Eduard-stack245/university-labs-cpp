#pragma once
// ---------------------------------------------------------------------------
// Weighted undirected graph stored as an adjacency matrix, with
//   * Prim's minimum spanning tree      (ASD lab 1)
//   * Dijkstra's shortest paths         (ASD lab 2)
// The labs had the 6x6 matrix hard-coded; here the graph is a class that can
// be built by hand or read from a text file:
//
//     6                      <- number of vertices
//     0 5 0 1 3 0            <- matrix rows; 0 means "no edge"
//     5 0 1 0 7 0
//     ...
// ---------------------------------------------------------------------------
#include <cstddef>
#include <istream>
#include <limits>
#include <stdexcept>
#include <vector>

namespace gx {

class Graph
{
public:
    using Weight = unsigned int;                 // 0 = no edge
    static constexpr unsigned long long INF = std::numeric_limits<unsigned long long>::max();

    struct Edge { int from, to; Weight weight; };
    struct MstResult { std::vector<Edge> edges; unsigned long long total = 0; bool connected = true; };
    struct PathResult { std::vector<unsigned long long> dist; std::vector<int> parent; };

    explicit Graph(int vertices = 0) : n_(vertices), m_(static_cast<std::size_t>(vertices), std::vector<Weight>(static_cast<std::size_t>(vertices), 0))
    {
        if (vertices < 0) throw std::invalid_argument("negative number of vertices");
    }

    int size() const { return n_; }

    // Adds (or changes) an undirected edge. weight 0 removes it.
    void setEdge(int a, int b, Weight weight)
    {
        check(a); check(b);
        if (a == b) throw std::invalid_argument("loops are not supported");
        m_[idx(a)][idx(b)] = weight;
        m_[idx(b)][idx(a)] = weight;
    }

    Weight weight(int a, int b) const { check(a); check(b); return m_[idx(a)][idx(b)]; }

    // Reads "n" followed by n*n numbers. The matrix must be symmetric with a zero diagonal.
    static Graph fromMatrix(std::istream& in)
    {
        int n = 0;
        if (!(in >> n) || n < 0) throw std::runtime_error("graph file: bad vertex count");
        Graph g(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!(in >> g.m_[idx(i)][idx(j)])) throw std::runtime_error("graph file: matrix is incomplete");
        for (int i = 0; i < n; i++) {
            if (g.m_[idx(i)][idx(i)] != 0) throw std::runtime_error("graph file: diagonal must be 0");
            for (int j = i + 1; j < n; j++)
                if (g.m_[idx(i)][idx(j)] != g.m_[idx(j)][idx(i)]) throw std::runtime_error("graph file: matrix must be symmetric");
        }
        return g;
    }

    // Prim's algorithm, O(n^2). If the graph is not connected, only the component
    // of `start` is covered and `connected` is false.
    MstResult primMst(int start = 0) const
    {
        MstResult r;
        if (n_ == 0) return r;
        check(start);
        std::vector<bool> inTree(idx(n_), false);
        std::vector<Weight> best(idx(n_), 0);     // cheapest edge into the tree, 0 = none yet
        std::vector<int> from(idx(n_), -1);
        inTree[idx(start)] = true;
        for (int v = 0; v < n_; v++) if (m_[idx(start)][idx(v)]) { best[idx(v)] = m_[idx(start)][idx(v)]; from[idx(v)] = start; }

        for (int added = 1; added < n_; added++) {
            int pick = -1;
            for (int v = 0; v < n_; v++)
                if (!inTree[idx(v)] && best[idx(v)] && (pick < 0 || best[idx(v)] < best[idx(pick)])) pick = v;
            if (pick < 0) { r.connected = false; break; }
            inTree[idx(pick)] = true;
            r.edges.push_back({from[idx(pick)], pick, best[idx(pick)]});
            r.total += best[idx(pick)];
            for (int v = 0; v < n_; v++) {
                const Weight w = m_[idx(pick)][idx(v)];
                if (!inTree[idx(v)] && w && (!best[idx(v)] || w < best[idx(v)])) { best[idx(v)] = w; from[idx(v)] = pick; }
            }
        }
        return r;
    }

    // Dijkstra's algorithm, O(n^2). dist[v] == INF if v is unreachable.
    PathResult dijkstra(int source) const
    {
        check(source);
        PathResult r;
        r.dist.assign(idx(n_), INF);
        r.parent.assign(idx(n_), -1);
        std::vector<bool> done(idx(n_), false);
        r.dist[idx(source)] = 0;
        for (int step = 0; step < n_; step++) {
            int u = -1;
            for (int v = 0; v < n_; v++)
                if (!done[idx(v)] && r.dist[idx(v)] != INF && (u < 0 || r.dist[idx(v)] < r.dist[idx(u)])) u = v;
            if (u < 0) break;
            done[idx(u)] = true;
            for (int v = 0; v < n_; v++) {
                const Weight w = m_[idx(u)][idx(v)];
                if (w && !done[idx(v)] && r.dist[idx(u)] + w < r.dist[idx(v)]) { r.dist[idx(v)] = r.dist[idx(u)] + w; r.parent[idx(v)] = u; }
            }
        }
        return r;
    }

    // Vertices of the shortest path source -> target (empty if unreachable).
    static std::vector<int> pathTo(const PathResult& r, int target, int source)
    {
        std::vector<int> path;
        if (r.dist[idx(target)] == INF) return path;
        for (int v = target; v != -1; v = r.parent[idx(v)]) path.insert(path.begin(), v);
        if (path.front() != source) path.clear();
        return path;
    }

private:
    static std::size_t idx(int v) { return static_cast<std::size_t>(v); }
    void check(int v) const { if (v < 0 || v >= n_) throw std::out_of_range("vertex index out of range"); }

    int n_;
    std::vector<std::vector<Weight>> m_;
};

} // namespace gx
