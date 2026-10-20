#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int sum_k = 0;

        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;

            bool possible = true;
            int prev_max = -1;

            for (int b = 0; b < n; b += k) {
                int drops = 0;
                int dropIdx = -1;

                // Check cyclic transitions within block [b, b + k - 1]
                for (int j = 0; j < k; ++j) {
                    int cur = nums[b + j];
                    int nxt = nums[b + (j + 1) % k];
                    if (cur > nxt) {
                        drops++;
                        dropIdx = j;
                    }
                }

                if (drops > 1) {
                    possible = false;
                    break;
                }

                int block_min, block_max;
                if (drops == 0) {
                    // All elements are identical or circularly non-decreasing
                    block_min = nums[b];
                    block_max = nums[b];
                } else {
                    // Exactly 1 drop: the sorted block starts at (dropIdx + 1) % k and ends at dropIdx
                    block_min = nums[b + (dropIdx + 1) % k];
                    block_max = nums[b + dropIdx];
                }

                // Check order across blocks
                if (prev_max != -1 && prev_max > block_min) {
                    possible = false;
                    break;
                }

                prev_max = block_max;
            }

            if (possible) {
                sum_k += k;
            }
        }

        return sum_k;
    }
};