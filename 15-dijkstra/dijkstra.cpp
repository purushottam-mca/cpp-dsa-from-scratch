// Dijkstra: shortest paths from one source, non-negative weights only.
// Greedy loop over a min heap: always settle the nearest unsettled vertex.
// The heap here is std::priority_queue; the hand-rolled version lives in 10-min-heap.
// Compile: g++ -std=c++17 -Wall -Wextra 15-dijkstra/dijkstra.cpp -o /tmp/dij && /tmp/dij

#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

class WeightedGraph {
public:
    explicit WeightedGraph(int vertices) : adj_(vertices) {}

    void addEdge(int u, int v, int w) {
        adj_[u].push_back({v, w});
        adj_[v].push_back({u, w});  // undirected; drop this line for directed
    }

    int size() const { return adj_.size(); }

    // Shortest distance from src to every vertex. Unreachable stays INF.
    std::vector<int> shortest(int src) const {
        const int INF = std::numeric_limits<int>::max();
        std::vector<int> dist(adj_.size(), INF);
        dist[src] = 0;
        using Step = std::pair<int, int>;  // distance, vertex
        std::priority_queue<Step, std::vector<Step>, std::greater<Step>> pq;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;  // stale entry, a better one won already
            for (auto [v, w] : adj_[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

private:
    std::vector<std::vector<std::pair<int, int>>> adj_;
};

int main() {
    // Classic small map: 0-1 (4), 0-2 (1), 2-1 (2), 1-3 (1), 2-3 (5), 3-4 (3).
    WeightedGraph g(5);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 1, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 3);

    // Best road to 1 goes through 2 (1+2), not the direct edge (4).
    std::vector<int> d = g.shortest(0);
    assert(d == std::vector<int>({0, 3, 1, 4, 7}));

    // From the far end the map mirrors.
    std::vector<int> back = g.shortest(4);
    assert(back[0] == 7 && back[3] == 3 && back[4] == 0);

    // A cut-off vertex is unreachable and stays INF.
    WeightedGraph h(3);
    h.addEdge(0, 1, 5);
    std::vector<int> dh = h.shortest(0);
    assert(dh[0] == 0 && dh[1] == 5);
    assert(dh[2] == std::numeric_limits<int>::max());

    std::cout << "All dijkstra checks passed.\n";
    return 0;
}
