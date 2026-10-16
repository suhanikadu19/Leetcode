#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0;
        long long sum_sq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;

    void apply(int node, int l, int r, long long val) {
        val %= MOD;
        long long len = (r - l + 1);
        
        // sum_sq = sum_sq + 2 * val * sum + val^2 * len
        long long term1 = tree[node].sum_sq;
        long long term2 = (2 * val % MOD) * tree[node].sum % MOD;
        long long term3 = (val * val % MOD) * len % MOD;
        
        tree[node].sum_sq = (term1 + term2 + term3) % MOD;
        tree[node].sum = (tree[node].sum + val * len) % MOD;
        tree[node].lazy = (tree[node].lazy + val) % MOD;
    }

    void pushDown(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            int mid = l + (r - l) / 2;
            apply(2 * node, l, mid, tree[node].lazy);
            apply(2 * node + 1, mid + 1, r, tree[node].lazy);
            tree[node].lazy = 0;
        }
    }

    void pushUp(int node) {
        tree[node].sum = (tree[2 * node].sum + tree[2 * node + 1].sum) % MOD;
        tree[node].sum_sq = (tree[2 * node].sum_sq + tree[2 * node + 1].sum_sq) % MOD;
    }

    void update(int node, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        pushDown(node, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid) update(2 * node, l, mid, ql, qr, val);
        if (qr > mid) update(2 * node + 1, mid + 1, r, ql, qr, val);
        pushUp(node);
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        tree.assign(4 * n, Node());
        unordered_map<int, int> last_pos;

        long long total_ans = 0;

        for (int j = 0; j < n; ++j) {
            int prev = last_pos.count(nums[j]) ? last_pos[nums[j]] : -1;
            
            // Add 1 to range [prev + 1, j]
            update(1, 0, n - 1, prev + 1, j, 1);
            
            // tree[1].sum_sq contains sum of d(i, j)^2 for all i in [0, j]
            total_ans = (total_ans + tree[1].sum_sq) % MOD;
            
            last_pos[nums[j]] = j;
        }

        return (total_ans % MOD + MOD) % MOD;
    }
};