#include <vector>

class Solution {
public:
    int uniquePaths(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MOD = 1e9 + 7;

        std::vector<std::vector<int>> dp(m, std::vector<int>(n, -1));

        // Simulates entering from (r, c) in direction `dir` (0 = Right, 1 = Down)
        // Returns the final landed cell {next_r, next_c}, or {-1, -1} if out of bounds.
        auto simulateMove = [&](int r, int c, int dir) -> std::pair<int, int> {
            int cr = r + (dir == 1 ? 1 : 0);
            int cc = c + (dir == 0 ? 1 : 0);

            // While within bounds and hitting mirrors, keep reflecting
            while (cr < m && cc < n && grid[cr][cc] == 1) {
                // If the mirror cell itself is the destination, check problem note:
                // "until either the last cell is reached, the robot moves out of bounds or moves to a non-mirror cell"
                if (cr == m - 1 && cc == n - 1) {
                    return {cr, cc};
                }

                if (dir == 0) { // entered moving right -> reflected down
                    cr += 1;
                    dir = 1;
                } else {        // entered moving down -> reflected right
                    cc += 1;
                    dir = 0;
                }
            }

            if (cr >= m || cc >= n) {
                return {-1, -1}; // out of bounds
            }
            return {cr, cc};
        };

        auto solve = [&](auto& self, int r, int c) -> int {
            if (r == m - 1 && c == n - 1) return 1;
            if (dp[r][c] != -1) return dp[r][c];

            long long ways = 0;

            // Option 1: Move Right (dir = 0)
            auto [r_next, c_next] = simulateMove(r, c, 0);
            if (r_next != -1) {
                ways = (ways + self(self, r_next, c_next)) % MOD;
            }

            // Option 2: Move Down (dir = 1)
            auto [r_down, c_down] = simulateMove(r, c, 1);
            if (r_down != -1) {
                ways = (ways + self(self, r_down, c_down)) % MOD;
            }

            return dp[r][c] = ways;
        };

        return solve(solve, 0, 0);
    }
};