#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;
const int INF = 1e9;
struct graph{
    vector<vector<int>> adj;
    vector<vector<int>> inverseAdj;
    void fill_inv_adj(){
        inverseAdj.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            for(int j = 0; j < adj[i].size(); j++){
                inverseAdj[adj[i][j]].push_back(i);
            }
        }
    }
    vector<int> connectComponent;
    int ccount = 0;
    vector<bool> hv;
    void dfs(int x){
        for(int i: adj[x]){
            if(hv[i]) continue;
            hv[i] = true;
            connectComponent[i] = ccount;
            dfs(i);
        }
    }
    vector<int> sorting(){
        fill_inv_adj();
        vector<int> inDeg(adj.size());
        for(int i = 0; i < inverseAdj.size(); i++){
            inDeg[i] = inverseAdj[i].size();
        }
        deque<int> cur;
        for(int i = 0; i < adj.size(); i++){
            if(inDeg[i] == 0){
                cur.push_back(i);
            }
        }
        vector<int> ans;
        while(!cur.empty()){
            int x = cur.front();
            ans.push_back(x);
            cur.pop_front();
            for(int i: adj[x]){
                inDeg[i]--;
                if(inDeg[i] == 0){
                    cur.push_back(i);
                }
            }
        }
        return ans;
    }
};
int main(){
    graph g;
    int n, m;
    cin >> n >> m;
    g.adj.resize(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.adj[u].push_back(v);
    }
    vector<int> v = g.sorting();
    int dp[n + 1];
    for(int i = 0; i <= n; i++){
        dp[i] = 0;
    }
    dp[0] = 0;
    //cout << g.inverseAdj[4][0] << endl;
    //return 0;
    for(int i = 0; i < v.size(); i++){
        for(int x: g.inverseAdj[v[i]]){
            //cout << dp[v[i]] << " ";
            dp[v[i]] = max(dp[v[i]], dp[x] + 1);
            //dp[v[i]] = max(dp[v[i]], 0)
        }
    }
    int myMax = 0;
    for(int i: dp){
        //cout << i << endl;
        myMax = max(myMax, i);
    }
    cout << myMax << endl;
}
