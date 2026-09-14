// Graph: undirected, adjacency list, with BFS, DFS, and cycle check.
// Vertices are numbered 0 to n-1. Neighbors stay in insert order.
// Compile: g++ -std=c++17 -Wall -Wextra 13-graph/graph.cpp -o /tmp/graph && /tmp/graph

#include <cassert>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

class Graph {
public:
    explicit Graph(int vertices) : adj_(vertices) {}

    void addEdge(int u, int v) {
        adj_[u].push_back(v);
        adj_[v].push_back(u);
    }

    int size() const { return adj_.size(); }

    // Breadth first: level by level. Shortest path in edges on unweighted graphs.
    std::vector<int> bfs(int start) const {
        std::vector<int> order;
        std::vector<bool> seen(adj_.size(), false);
        std::queue<int> q;
        q.push(start);
        seen[start] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj_[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }
        return order;
    }

    // Depth first, iterative: go deep before going wide.
    std::vector<int> dfs(int start) const {
        std::vector<int> order;
        std::vector<bool> seen(adj_.size(), false);
        std::stack<int> s;
        s.push(start);
        seen[start] = true;
        while (!s.empty()) {
            int u = s.top();
            s.pop();
            order.push_back(u);
            // Push reversed so the first neighbor is visited first.
            for (auto it = adj_[u].rbegin(); it != adj_[u].rend(); ++it) {
                if (!seen[*it]) {
                    seen[*it] = true;
                    s.push(*it);
                }
            }
        }
        return order;
    }

    // Undirected cycle check: BFS that remembers each node's parent.
    bool hasCycle() const {
        std::vector<bool> seen(adj_.size(), false);
        for (int i = 0; i < size(); ++i) {
            if (!seen[i] && bfs_cycle_from(i, seen)) return true;
        }
        return false;
    }

    int components() const {
        std::vector<bool> seen(adj_.size(), false);
        int count = 0;
        for (int i = 0; i < size(); ++i) {
            if (!seen[i]) {
                ++count;
                mark_reachable(i, seen);
            }
        }
        return count;
    }

private:
    bool bfs_cycle_from(int start, std::vector<bool>& seen) const {
        std::queue<std::pair<int, int>> q;  // node, parent
        q.push({start, -1});
        seen[start] = true;
        while (!q.empty()) {
            auto [u, parent] = q.front();
            q.pop();
            for (int v : adj_[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    q.push({v, u});
                } else if (v != parent) {
                    return true;  // reached an old node that is not our parent
                }
            }
        }
        return false;
    }

    void mark_reachable(int start, std::vector<bool>& seen) const {
        std::queue<int> q;
        q.push(start);
        seen[start] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj_[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }
    }

    std::vector<std::vector<int>> adj_;
};

int main() {
    // Square with a tail: 0-1-3-2-0 plus 3-4.
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    assert(g.bfs(0) == std::vector<int>({0, 1, 2, 3, 4}));
    assert(g.dfs(0) == std::vector<int>({0, 1, 3, 4, 2}));
    assert(g.hasCycle());      // the square loops back on itself
    assert(g.components() == 1);

    // Two separate pieces, no cycles.
    Graph h(4);
    h.addEdge(0, 1);
    h.addEdge(2, 3);
    assert(!h.hasCycle());
    assert(h.components() == 2);
    assert(h.bfs(2) == std::vector<int>({2, 3}));

    // Single lonely vertex.
    Graph s(1);
    assert(s.bfs(0) == std::vector<int>({0}));
    assert(!s.hasCycle());
    assert(s.components() == 1);

    std::cout << "All graph checks passed.\n";
    return 0;
}
