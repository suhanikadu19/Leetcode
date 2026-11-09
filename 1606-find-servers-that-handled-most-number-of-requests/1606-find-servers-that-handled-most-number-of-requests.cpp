#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // Tracks how many requests each server handled
        vector<int> count(k, 0);

        // All servers are initially free: {0, 1, ..., k - 1}
        set<int> free_servers;
        for (int i = 0; i < k; ++i) {
            free_servers.insert(i);
        }

        // Min-heap to store {finish_time, server_id}
        priority_queue<pair<long long, int>, 
                       vector<pair<long long, int>>, 
                       greater<pair<long long, int>>> busy;

        for (int i = 0; i < arrival.size(); ++i) {
            long long cur_time = arrival[i];

            // Free up all servers whose work is finished by cur_time
            while (!busy.empty() && busy.top().first <= cur_time) {
                free_servers.insert(busy.top().second);
                busy.pop();
            }

            // All servers are busy; drop this request
            if (free_servers.empty()) {
                continue;
            }

            // Find the first available server >= (i % k)
            int target = i % k;
            auto it = free_servers.lower_bound(target);

            // If none found >= target, wrap around to the first available server
            if (it == free_servers.end()) {
                it = free_servers.begin();
            }

            int assigned_server = *it;
            free_servers.erase(it);

            count[assigned_server]++;
            busy.push({cur_time + load[i], assigned_server});
        }

        // Find the maximum number of requests handled
        int max_handled = *max_element(count.begin(), count.end());

        // Collect all servers that handled max_handled requests
        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (count[i] == max_handled) {
                result.push_back(i);
            }
        }

        return result;
    }
};