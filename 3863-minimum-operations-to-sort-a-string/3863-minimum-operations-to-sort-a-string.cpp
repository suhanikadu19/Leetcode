#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // Already sorted
        if (is_sorted(s.begin(), s.end())) {
            return 0;
        }

        // Proper substrings have length <= n - 1.
        // For n = 2, only length 1 substrings can be chosen, which cannot swap characters.
        if (n <= 2) {
            return -1;
        }

        char min_ch = *min_element(s.begin(), s.end());
        char max_ch = *max_element(s.begin(), s.end());

        // Can be sorted in 1 operation if min is at the start or max is at the end
        if (s[0] == min_ch || s[n - 1] == max_ch) {
            return 1;
        }

        // Can be sorted in 2 operations if min exists in s[0..n-2] OR max exists in s[1..n-1]
        bool min_in_prefix = false;
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == min_ch) {
                min_in_prefix = true;
                break;
            }
        }

        bool max_in_suffix = false;
        for (int i = 1; i < n; ++i) {
            if (s[i] == max_ch) {
                max_in_suffix = true;
                break;
            }
        }

        if (min_in_prefix || max_in_suffix) {
            return 2;
        }

        // Otherwise, s[0] is the unique maximum and s[n-1] is the unique minimum
        return 3;
    }
};