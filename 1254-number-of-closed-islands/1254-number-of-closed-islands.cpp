#include <vector>

using namespace std;

class Solution {
private:
    int m, n;

    void dfs(vector<vector<int>>& grid, int r, int c) {
        // Boundary and water check
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 1) {
            return;
        }

        // Mark current land cell as visited by turning it into water
        grid[r][c] = 1;

        // Traverse in all 4 cardinal directions
        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c + 1);
        dfs(grid, r, c - 1);
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        // Step 1: Flood-fill all '0's connected to the boundary
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 0) dfs(grid, i, 0);
            if (grid[i][n - 1] == 0) dfs(grid, i, n - 1);
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 0) dfs(grid, 0, j);
            if (grid[m - 1][j] == 0) dfs(grid, m - 1, j);
        }

        // Step 2: Count remaining isolated islands in the interior
        int closedIslands = 0;
        for (int i = 1; i < m - 1; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                if (grid[i][j] == 0) {
                    ++closedIslands;
                    dfs(grid, i, j);
                }
            }
        }

        return closedIslands;
    }
};