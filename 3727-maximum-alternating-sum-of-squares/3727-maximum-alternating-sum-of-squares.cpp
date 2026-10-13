#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    long long maxAlternatingSum(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<long long> squares(n);
        
        for (int i = 0; i < n; ++i) {
            squares[i] = 1LL * nums[i] * nums[i];
        }
        
        // Sort squares in descending order
        std::sort(squares.begin(), squares.end(), std::greater<long long>());
        
        int positive_count = (n + 1) / 2;
        long long max_score = 0;
        
        for (int i = 0; i < positive_count; ++i) {
            max_score += squares[i];
        }
        for (int i = positive_count; i < n; ++i) {
            max_score -= squares[i];
        }
        
        return max_score;
    }
};