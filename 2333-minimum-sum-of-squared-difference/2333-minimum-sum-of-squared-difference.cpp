#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

class Solution {
public:
    long long minSumSquareDiff(std::vector<int>& nums1, std::vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        
        int max_diff = 0;
        std::vector<int> diff(n);
        for (int i = 0; i < n; ++i) {
            diff[i] = std::abs(nums1[i] - nums2[i]);
            max_diff = std::max(max_diff, diff[i]);
        }
        
        // If total operations can reduce all differences to 0
        long long total_diff = 0;
        for (int d : diff) total_diff += d;
        if (total_diff <= k) return 0;
        
        // Frequency bucket of differences
        std::vector<int> count(max_diff + 1, 0);
        for (int d : diff) {
            count[d]++;
        }
        
        // Greedily reduce the highest differences
        for (int v = max_diff; v > 0 && k > 0; --v) {
            if (count[v] == 0) continue;
            
            long long take = std::min((long long)count[v], k);
            count[v] -= take;
            count[v - 1] += take;
            k -= take;
            
            // If operations remain and all items at `v` moved to `v-1`,
            // we will process `v-1` in the next iteration.
            // If k was not enough to move all, k is now 0 and loop ends.
        }
        
        // Calculate the sum of squared differences
        long long ans = 0;
        for (long long v = 1; v <= max_diff; ++v) {
            if (count[v] > 0) {
                ans += (long long)count[v] * v * v;
            }
        }
        
        return ans;
    }
};