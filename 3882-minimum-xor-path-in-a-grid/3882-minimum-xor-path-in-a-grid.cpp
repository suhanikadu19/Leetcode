#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Assuming values < 1024, bitset of size 1024 covers all reachable XOR sums
        const int MAX_XOR = 1024;
        vector<bitset<MAX_XOR>> dp(n);
        
        // Initialize (0, 0)
        dp[0].set(grid[0][0]);
        
        // First row
        for (int j = 1; j < n; ++j) {
            int val = grid[0][j];
            for (int k = 0; k < MAX_XOR; ++k) {
                if (dp[j - 1].test(k)) {
                    dp[j].set(k ^ val);
                }
            }
        }
        
        // Remaining rows
        for (int i = 1; i < m; ++i) {
            // First column of row i
            bitset<MAX_XOR> next_first;
            int val0 = grid[i][0];
            for (int k = 0; k < MAX_XOR; ++k) {
                if (dp[0].test(k)) {
                    next_first.set(k ^ val0);
                }
            }
            dp[0] = next_first;
            
            // Other columns
            for (int j = 1; j < n; ++j) {
                bitset<MAX_XOR> combined = dp[j] | dp[j - 1]; // from top or left
                bitset<MAX_XOR> current;
                int val = grid[i][j];
                
                for (int k = 0; k < MAX_XOR; ++k) {
                    if (combined.test(k)) {
                        current.set(k ^ val);
                    }
                }
                dp[j] = current;
            }
        }
        
        // Find the minimum reachable XOR value at (m - 1, n - 1)
        for (int k = 0; k < MAX_XOR; ++k) {
            if (dp[n - 1].test(k)) {
                return k;
            }
        }
        
        return 0;
    }
};