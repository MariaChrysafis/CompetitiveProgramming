class Solution {
public:
    vector<vector<long long>> adj;
    vector<long long> sub;
    int dfs (int curNode, int prevNode) {
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                sub[curNode] += dfs(i, curNode);
            }
        }
        return sub[curNode];
    }
    int countHighestScoreNodes(vector<int>& parents) {
        adj.resize(parents.size());
        sub.resize(parents.size());
        for (int i = 1; i < parents.size(); i++) {
            adj[i].push_back(parents[i]);
            adj[parents[i]].push_back(i);
        }
        dfs(0, -1);
        vector<long long> v;
        for (int i = 0; i < parents.size(); i++) {
            if (adj[i].size() == 1) {
                v.push_back(parents.size() - 1);
                continue;
            } 
            long long ans = 1;
            for (int j: adj[i]) {
                if (j != parents[i]) {
                    ans *= sub[j];
                }
            }
            if (i != 0) {
                ans *= (adj.size() - sub[i]);
            }
            v.push_back(ans);
        }
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        int cntr = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == v[0]) {
                cntr++;
            }
        }
        return cntr;
    }
};
