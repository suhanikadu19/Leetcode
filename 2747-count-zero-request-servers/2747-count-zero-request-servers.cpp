#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();
        
        // Pair: {query_time, original_index}
        vector<pair<int, int>> sortedQueries(m);
        for (int i = 0; i < m; i++) {
            sortedQueries[i] = {queries[i], i};
        }
        
        // Sort queries by time
        sort(sortedQueries.begin(), sortedQueries.end());
        
        // Sort logs by time (logs[i][1])
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        vector<int> result(m);
        vector<int> serverCount(n + 1, 0);
        int activeServers = 0;
        
        int l = 0;
        int r = 0;
        int logLen = logs.size();
        
        for (const auto& [qTime, qIndex] : sortedQueries) {
            int startTime = qTime - x;
            
            // Expand window: include all logs with time <= qTime
            while (r < logLen && logs[r][1] <= qTime) {
                int serverId = logs[r][0];
                if (serverCount[serverId] == 0) {
                    activeServers++;
                }
                serverCount[serverId]++;
                r++;
            }
            
            // Shrink window: exclude all logs with time < startTime
            while (l < logLen && logs[l][1] < startTime) {
                int serverId = logs[l][0];
                serverCount[serverId]--;
                if (serverCount[serverId] == 0) {
                    activeServers--;
                }
                l++;
            }
            
            // Total servers minus servers that received at least one request
            result[qIndex] = n - activeServers;
        }
        
        return result;
    }
};