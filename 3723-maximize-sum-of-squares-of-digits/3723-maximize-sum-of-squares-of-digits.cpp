
            #include <string>

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num) {
            return "";
        }

        int count9 = sum / 9;
        int rem = sum % 9;
        int count0 = num - count9 - (rem > 0 ? 1 : 0);

        string ans = "";
        ans.append(count9, '9');
        if (rem > 0) {
            ans.push_back('0' + rem);
        }
        ans.append(count0, '0');

        return ans;
    }
};