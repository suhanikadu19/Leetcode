class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        // Find the index of 0
        int k = 0;
        while (nums[k] != 0) {
            k++;
        }

        // Check if circularly ascending
        bool is_asc = true;
        for (int i = 0; i < n; i++) {
            if (nums[(k + i) % n] != i) {
                is_asc = false;
                break;
            }
        }

        if (is_asc) {
            if (k == 0) return 0;
            // Option 1: Rotate left k times
            // Option 2: Reverse, Rotate left (n - k) times, Reverse
            return min(k, (n - k) + 2);
        }

        // Check if circularly descending
        bool is_desc = true;
        for (int i = 0; i < n; i++) {
            if (nums[(k - i + n) % n] != i) {
                is_desc = false;
                break;
            }
        }

        if (is_desc) {
            // Option 1: Reverse first, then shift left (n - 1 - k) times
            int opt1 = 1 + (n - 1 - k);
            // Option 2: Shift left so 0 reaches index n - 1, then reverse
            int opt2 = ((k + 1) % n) + 1;
            return min(opt1, opt2);
        }

        return -1;
    }
};