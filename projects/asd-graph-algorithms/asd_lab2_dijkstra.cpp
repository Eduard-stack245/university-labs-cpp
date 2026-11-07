#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

#include "lab_compat.h"

namespace {
constexpr int firstVertex = 1;
constexpr int lastVertex = 6;
constexpr int infinity = (std::numeric_limits<int>::max)();
using Graph = std::map<int, std::map<int, int>>;

const Graph graph{
    {1, {{2, 5}, {4, 1}, {5, 3}}},
    {2, {{1, 5}, {3, 1}, {5, 7}}},
    {3, {{2, 1}, {5, 5}, {6, 4}}},
    {4, {{1, 1}, {5, 2}}},
    {5, {{1, 3}, {2, 7}, {3, 5}, {4, 2}, {6, 10}}},
    {6, {{3, 4}, {5, 10}}}
};

bool readVertex(const char* prompt, int& vertex)
{
    for (;;) {
        std::cout << prompt;
        if (!(std::cin >> vertex)) return false;
        if (vertex >= firstVertex && vertex <= lastVertex) return true;
        std::cout << "не вірно введена вершина (1-6)\n";
    }
}

// Dijkstra for the nonnegative edge weights of this laboratory's graph.
std::vector<int> shortestPath(int start, int destination, int& totalDistance)
{
    std::array<int, lastVertex + 1> distance;
    std::array<int, lastVertex + 1> previous{};
    std::array<bool, lastVertex + 1> visited{};
    distance.fill(infinity);
    distance[start] = 0;

    for (int step = firstVertex; step <= lastVertex; ++step) {
        int current = 0;
        for (int v = firstVertex; v <= lastVertex; ++v) {
            if (!visited[v] && distance[v] != infinity &&
                (current == 0 || distance[v] < distance[current])) current = v;
        }
        if (current == 0 || current == destination) break;
        visited[current] = true;
        for (const auto& edge : graph.at(current)) {
            const int next = edge.first;
            const int weight = edge.second;
            if (!visited[next] && distance[current] <= infinity - weight &&
                distance[current] + weight < distance[next]) {
                distance[next] = distance[current] + weight;
                previous[next] = current;
            }
        }
    }

    totalDistance = distance[destination];
    if (totalDistance == infinity) return {};
    std::vector<int> path;
    for (int vertex = destination; vertex != 0; vertex = previous[vertex]) {
        path.push_back(vertex);
        if (vertex == start) break;
    }
    std::reverse(path.begin(), path.end());
    return path;
}
} // namespace

int main()
{
    lab::init_console();
    std::cout << "Вивід матриці:\n";
    for (int row = firstVertex; row <= lastVertex; ++row) {
        for (int col = firstVertex; col <= lastVertex; ++col) {
            const auto edge = graph.at(row).find(col);
            std::cout << std::setw(4) << (edge == graph.at(row).end() ? 0 : edge->second);
        }
        std::cout << '\n';
    }

    std::cout << "\nНомер вершин шляху:\n";
    int start = 0;
    int destination = 0;
    if (!readVertex("Перша вершина - ", start) ||
        !readVertex("Друга вершина - ", destination)) return 1;

    int distance = infinity;
    const std::vector<int> path = shortestPath(start, destination, distance);
    if (path.empty()) {
        std::cout << "Шлях між вершинами відсутній\n";
        return 0;
    }
    std::cout << "Відстань: " << distance << "\nШлях:";
    for (std::size_t i = 0; i < path.size(); ++i)
        std::cout << (i == 0 ? " " : ", ") << path[i];
    std::cout << '\n';
    return 0;
}
