class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        vector<int> bitCount(31, 0);

        // Step 1: Count frequencies of each bit position
        for (int x : nums) {
            for (int b = 0; b < 31; ++b) {
                if ((x >> b) & 1) {
                    bitCount[b]++;
                }
            }
        }

        long long totalSum = 0;

        // Step 2: Greedily build the k largest numbers
        for (int i = 0; i < k; ++i) {
            long long currentVal = 0;
            for (int b = 0; b < 31; ++b) {
                if (bitCount[b] > 0) {
                    currentVal |= (1LL << b);
                    bitCount[b]--;
                }
            }
            totalSum = (totalSum + (currentVal % MOD) * (currentVal % MOD)) % MOD;
        }

        return totalSum;
    }
};