#include <vector>
#include <algorithm>

class Solution {
public:
    int minMoves(std::vector<int>& nums) {
        int min_val = *std::min_element(nums.begin(), nums.end());
        int moves = 0;
        
        for (int x : nums) {
            moves += (x - min_val);
        }
        
        return moves;
    }
};