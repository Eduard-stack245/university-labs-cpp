# graph-algorithms

**English** | [Українська](README.uk.md)

Prim's minimum spanning tree and Dijkstra's shortest paths as a small reusable class.
The ASD labs [asd-graph-algorithms](../asd-graph-algorithms) had one hard-coded 6x6 matrix; here the graph is read from a file.

| Program | What it does |
|---|---|
| `graph_demo` | `graph_demo [file] [source vertex]` - prints the spanning tree and the shortest path to every vertex (default: `graph6.txt`, vertex 1) |
| `sparse_tests` | self-checking tests of `SparseGraph` (see below): same answers as the matrix classes on 300 random graphs, plus a chain of 200 000 vertices |
| `graph_tests` | self-checking tests: Prim vs Kruskal and Dijkstra vs Floyd-Warshall on the lab graph and 300 random graphs (connected and not), plus input validation |

`Graph.hpp` (header-only):

```cpp
std::ifstream in("graph6.txt");
gx::Graph g = gx::Graph::fromMatrix(in);
auto mst = g.primMst();                       // mst.edges, mst.total, mst.connected
auto sp  = g.dijkstra(0);                     // sp.dist[v], sp.parent[v]
auto path = gx::Graph::pathTo(sp, 5, 0);      // vertices 0 -> ... -> 5
```

## SparseGraph - for big graphs
`SparseGraph.hpp` solves the same problems for sparse graphs: adjacency lists (memory O(V + E) instead of O(V^2)),
Dijkstra with a priority queue (O((V + E) log V)) and Kruskal's algorithm (sort the edges + union-find).

```cpp
gx::SparseGraph s(200000);
s.addEdge(0, 1, 5);                       // undirected, weight > 0; parallel edges are allowed (the cheapest wins)
auto sp  = s.dijkstra(0);                 // same result type as Graph::dijkstra
auto mst = s.kruskalMst();                // spanning forest if the graph is not connected (mst.connected == false)
auto s2  = gx::SparseGraph::fromGraph(g); // convert a matrix graph
```
A chain of 200 000 vertices works in the tests; the matrix version would need about 160 GB for it.

## File format
```
6              <- number of vertices
0 5 0 1 3 0    <- adjacency matrix, 0 = no edge; must be symmetric with a zero diagonal
5 0 1 0 7 0
0 1 0 0 5 4
1 0 0 0 2 0
3 7 5 2 0 10
0 0 4 0 10 0
```

## Requirements
A C++17 compiler (MSVC 2019+, GCC, Clang) and CMake 3.10+.

## Build and run
```
cmake -S . -B build
cmake --build build
./build/graph_demo
./build/graph_tests
./build/sparse_tests
```
Visual Studio: `File -> Open -> Folder...`, pick this folder, choose a program in the toolbar, Ctrl+F5.

## Notes
- On the lab graph the results are the same as in the original labs: spanning tree weight 13, shortest path 1 -> 6 has length 10 (1-2-3-6).
- `Graph` keeps the simple O(n^2) matrix versions from the labs; `SparseGraph` is the scalable version. Possible next steps: directed graphs, reading `SparseGraph` from an edge-list file, a `--dot` export for Graphviz.
