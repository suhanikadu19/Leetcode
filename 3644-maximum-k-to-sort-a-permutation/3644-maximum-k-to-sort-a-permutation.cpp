class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i) {
                if (ans == -1) {
                    ans = nums[i];
                } else {
                    ans &= nums[i];
                }
            }
        }
        
        // If the array is already sorted, ans remains -1, so return 0
        return (ans == -1) ? 0 : ans;
    }
};