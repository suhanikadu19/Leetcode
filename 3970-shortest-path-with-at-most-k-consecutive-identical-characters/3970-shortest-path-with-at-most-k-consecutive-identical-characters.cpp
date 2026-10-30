#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        if (n == 1) return 0;
        if (k < 1) return -1;

        // Build adjacency list: u -> vector of {v, weight}
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        // dist[u][c]: min distance to reach node u with consecutive label count c
        const long long INF = 1e18;
        vector<vector<long long>> dist(n, vector<long long>(k + 1, INF));

        // min-heap storing {cost, node, count}
        using State = tuple<long long, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, c] = pq.top();
            pq.pop();

            if (u == n - 1) return (int)d;
            if (d > dist[u][c]) continue;

            for (const auto& [v, w] : adj[u]) {
                if (labels[v] == labels[u]) {
                    int next_c = c + 1;
                    if (next_c <= k && d + w < dist[v][next_c]) {
                        dist[v][next_c] = d + w;
                        pq.push({d + w, v, next_c});
                    }
                } else {
                    int next_c = 1;
                    if (d + w < dist[v][next_c]) {
                        dist[v][next_c] = d + w;
                        pq.push({d + w, v, next_c});
                    }
                }
            }
        }

        return -1;
    }
};