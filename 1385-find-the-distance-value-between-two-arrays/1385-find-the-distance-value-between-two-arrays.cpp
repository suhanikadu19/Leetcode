#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    int findTheDistanceValue(std::vector<int>& arr1, std::vector<int>& arr2, int d) {
        // arr2 ko sort karenge taaki binary search use kar sakein
        std::sort(arr2.begin(), arr2.end());
        int count = 0;

        for (int val : arr1) {
            // Condition: |val - x| <= d  =>  val - d <= x <= val + d
            // lower_bound se hum first element dhoondhte hain jo >= (val - d) ho
            auto it = std::lower_bound(arr2.begin(), arr2.end(), val - d);

            // Agar aisa koi element milta hai aur wo <= (val + d) hai,
            // toh condition satisfy nahi hogi
            if (it != arr2.end() && *it <= val + d) {
                continue;
            }

            // Agar range [val - d, val + d] mein koi element nahi mila
            count++;
        }

        return count;
    }
};