#include <vector>

using namespace std;

class Solution {
private:
    const long long MOD = 1e9 + 7;
    vector<vector<long long>> comb;

    // Precompute Pascal's Triangle for combinations
    void buildPascalTriangle(int n) {
        comb.assign(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; ++i) {
            comb[i][0] = 1;
            for (int j = 1; j <= i; ++j) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }
    }

    long long dfs(const vector<int>& nums) {
        int m = nums.size();
        if (m <= 2) return 1;

        int root = nums[0];
        vector<int> left, right;

        for (int i = 1; i < m; ++i) {
            if (nums[i] < root) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }

        long long waysLeft = dfs(left);
        long long waysRight = dfs(right);

        // comb[|left| + |right|][|left|] * waysLeft * waysRight % MOD
        long long totalWays = comb[left.size() + right.size()][left.size()];
        totalWays = (totalWays * waysLeft) % MOD;
        totalWays = (totalWays * waysRight) % MOD;

        return totalWays;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        buildPascalTriangle(n);
        return (dfs(nums) - 1 + MOD) % MOD;
    }
};