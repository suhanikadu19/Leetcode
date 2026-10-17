#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    int getDigitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

public:
    int minSwaps(std::vector<int>& nums) {
        int n = nums.size();
        
        // Store indices and sort them based on the problem's criteria
        std::vector<int> targetIdx(n);
        std::iota(targetIdx.begin(), targetIdx.end(), 0);
        
        std::vector<int> digitSums(n);
        for (int i = 0; i < n; ++i) {
            digitSums[i] = getDigitSum(nums[i]);
        }
        
        std::sort(targetIdx.begin(), targetIdx.end(), [&](int a, int b) {
            if (digitSums[a] != digitSums[b]) {
                return digitSums[a] < digitSums[b];
            }
            return nums[a] < nums[b];
        });
        
        // Find permutation cycles
        std::vector<bool> visited(n, false);
        int totalSwaps = 0;
        
        for (int i = 0; i < n; ++i) {
            // Already visited or already at correct position
            if (visited[i] || targetIdx[i] == i) {
                continue;
            }
            
            int cycleSize = 0;
            int curr = i;
            
            while (!visited[curr]) {
                visited[curr] = true;
                curr = targetIdx[curr];
                cycleSize++;
            }
            
            if (cycleSize > 1) {
                totalSwaps += (cycleSize - 1);
            }
        }
        
        return totalSwaps;
    }
};