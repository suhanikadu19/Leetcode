#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class FenwickTree {
    int n;
    vector<int> tree;
public:
    FenwickTree(int n) : n(n), tree(n + 2, 0) {}

    void update(int i, int val) {
        for (; i <= n; i += i & -i) {
            tree[i] ^= val;
        }
    }

    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum ^= tree[i];
        }
        return sum;
    }
};

class Solution {
    int timer;
    vector<int> tin, tout, depth;
    vector<int> root_mask;
    vector<vector<int>> up;
    vector<vector<int>> adj;
    int LOG;

    void dfs(int u, int p, int d, int current_mask, const string& s) {
        tin[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;
        for (int j = 1; j < LOG; ++j) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        current_mask ^= (1 << (s[u] - 'a'));
        root_mask[u] = current_mask;

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, current_mask, s);
            }
        }
        tout[u] = timer;
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int j = LOG - 1; j >= 0; --j) {
            if (depth[u] - (1 << j) >= depth[v]) {
                u = up[u][j];
            }
        }
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        adj.assign(n, vector<int>());
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);
        root_mask.assign(n, 0);
        up.assign(n, vector<int>(LOG, 0));
        timer = 0;

        dfs(0, 0, 0, 0, s);

        FenwickTree bit(n);
        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                if (s[u] != c) {
                    int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                    bit.update(tin[u], delta);
                    bit.update(tout[u] + 1, delta);
                    s[u] = c;
                }
            } else {
                int u, v;
                ss >> u >> v;

                int lca = get_lca(u, v);
                int mask_u = root_mask[u] ^ bit.query(tin[u]);
                int mask_v = root_mask[v] ^ bit.query(tin[v]);
                int lca_val = (1 << (s[lca] - 'a'));

                int path_mask = mask_u ^ mask_v ^ lca_val;

                ans.push_back((path_mask & (path_mask - 1)) == 0);
            }
        }

        return ans;
    }
};