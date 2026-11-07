# Roadmap

**English** | [Українська](ROADMAP.uk.md)

My plans and ideas for the next steps. Notes on the existing code: [NOTES.md](NOTES.md).

## Done
- **[random-toolkit](../projects/random-toolkit)** - the four ASD generators as std-compatible engines, a chi-square tester and `BasicRandom<Engine>`.
- **[random-class](../projects/random-class)** - `NextBool`, `NextGaussian`, `Shuffle`, `Choice` and its own tests (the old API is unchanged).
- **[sorting-algorithms](../projects/sorting-algorithms)** - self-checking tests (they found and fixed three bugs) and a benchmark with CSV output.
- **[graph-algorithms](../projects/graph-algorithms)** - `Graph` (matrix) and `SparseGraph` (adjacency lists, priority queue, Kruskal), tested against Kruskal and Floyd-Warshall.
- **[records-database](../projects/records-database)** - one `Table` class with typed columns, CSV, UTF-8 search, sorting, statistics, a sorted `Index` and a menu program.
- **[textstat](../projects/textstat)** - a command-line text statistics tool that understands UTF-8.
- **[vector-class](../projects/vector-class)** - `Vector<T>` with the rule of five, iterators and exception safety.

## Next
### Algorithms toolkit
- a custom comparator for the sorts; binary search and the recursion examples (`lab13_*`) as library functions;
- one shared test runner (Catch2 / GoogleTest) instead of the small hand-written checks;
- graphs: directed graphs, reading `SparseGraph` from an edge-list file, a `--dot` export for Graphviz.

### Random toolkit
- more statistical tests (runs test, serial correlation) and a period finder;
- a thread-local engine for `Random`.

### Records database
- keep the index up to date on `add`, indexes on several columns, schema read from the CSV header, JSON export.

### Smaller projects
- `textstat`: CSV output, several files in one report.
- `vector-class`: its own iterator class, `insert` / `erase` of ranges, a `push_back` benchmark against `std::vector`.
- `utility-payments`: read the tariffs from CSV/JSON instead of six hard-coded items, save a history.

## Cleanup ideas (the same exercise written twice)
- Taylor series for e^x: `lab06_03` and `exp_series`.
- Function table: `lab06_01` / `lab06_02` and `function_table`.
- Text analysis: `text_console` and `text_from_file`.
- Clothes table: `clothes_table` and `clothes_csv`.

## Windows-only ideas (`legacy-windows/`)
- `futkeeper-winforms` and `sort-prog-winforms` could be rewritten cross-platform (Qt or Dear ImGui) on top of the portable libraries above.
- `winapi-*` conchoid drawing: replace GDI with a small SDL/SFML program, or export the curve to SVG.

## Kept as a record of progress
`lab05-*`, `lab06-*`, `lab07-*`, `lab13-*`, `numbers-and-functions`, `arrays-and-matrices` -
short first-year exercises. No need to develop them further.
