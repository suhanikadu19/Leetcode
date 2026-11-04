#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
    multiset<long long> low, high;
    long long sum_low = 0, sum_high = 0;
    int k_low, k_high;

    void add(long long val) {
        if (low.empty() || val <= *low.rbegin()) {
            low.insert(val);
            sum_low += val;
        } else {
            high.insert(val);
            sum_high += val;
        }
        balance();
    }

    void remove(long long val) {
        auto it = low.find(val);
        if (it != low.end()) {
            sum_low -= val;
            low.erase(it);
        } else {
            it = high.find(val);
            sum_high -= val;
            high.erase(it);
        }
        balance();
    }

    void balance() {
        while ((int)low.size() > k_low) {
            auto it = prev(low.end());
            long long val = *it;
            sum_low -= val;
            low.erase(it);
            high.insert(val);
            sum_high += val;
        }
        while ((int)low.size() < k_low && !high.empty()) {
            auto it = high.begin();
            long long val = *it;
            sum_high -= val;
            high.erase(it);
            low.insert(val);
            sum_low += val;
        }
    }

    long long get_cost() {
        long long median = *low.rbegin();
        long long left_cost = (long long)low.size() * median - sum_low;
        long long right_cost = sum_high - (long long)high.size() * median;
        return left_cost + right_cost;
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        k_low = (x + 1) / 2;
        k_high = x - k_low;

        // cost[i] = operations to equalize subarray ending at index i - 1 (1-indexed)
        vector<long long> cost(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            add(nums[i]);
            if (i >= x) {
                remove(nums[i - x]);
            }
            if (i >= x - 1) {
                cost[i + 1] = get_cost();
            }
        }

        // dp[c][i]: min cost picking c subarrays within nums[0 ... i-1]
        // Base case: dp[0][i] = 0, others initialized to infinity
        const long long INF = 1e18;
        vector<long long> prev_dp(n + 1, 0);
        vector<long long> curr_dp(n + 1, INF);

        for (int c = 1; c <= k; ++c) {
            fill(curr_dp.begin(), curr_dp.end(), INF);
            for (int i = c * x; i <= n; ++i) {
                // Option 1: Do not pick subarray ending at i
                curr_dp[i] = curr_dp[i - 1];
                // Option 2: Pick subarray of length x ending at i
                if (prev_dp[i - x] != INF) {
                    curr_dp[i] = min(curr_dp[i], prev_dp[i - x] + cost[i]);
                }
            }
            prev_dp = curr_dp;
        }

        return curr_dp[n];
    }
};