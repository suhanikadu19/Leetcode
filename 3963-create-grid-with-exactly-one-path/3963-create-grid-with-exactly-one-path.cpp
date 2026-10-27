#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> createGrid(int m, int n) {
        // Initialize an m x n grid filled with obstacles '#'
        std::vector<std::string> grid(m, std::string(n, '#'));

        // Carve path across row 0: (0, 0) to (0, n - 1)
        for (int j = 0; j < n; ++j) {
            grid[0][j] = '.';
        }

        // Carve path down column n - 1: (0, n - 1) to (m - 1, n - 1)
        for (int i = 0; i < m; ++i) {
            grid[i][n - 1] = '.';
        }

        return grid;
    }
};