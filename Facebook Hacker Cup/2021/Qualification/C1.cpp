#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <map>
using namespace std;
const int INF = 1e9;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
struct Tree{
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> exit;
    int cntr = 1;
    int lg2;
    void dfs(int u, int prev){
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for(int i = 1; i <= lg2; i++){
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for(int v: adj[u]){
            if(v != prev){
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }
    bool isAncestor(int u, int v){
        //is u an ancestor of v
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }
    int leastCommonAncestor(int u, int v){
        if(isAncestor(u, v)){
            return u;
        }
        if(isAncestor(v, u)){
            return v;
        }
        for(int i = lg2; i >= 0; i--){
            if(!isAncestor(dp[u][i], v)){
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    void read(long long n){
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
    }
};
struct Graph{
    vector<vector<int>> adj;
    vector<long long> weight;
    vector<long long> bfs(int x){
        queue<pair<int,long long>> q;
        vector<bool> hasVisited(adj.size());
        vector<long long> shortest_distance(adj.size());
        for(int i = 0; i < shortest_distance.size(); i++){
            hasVisited[i] = false;
            shortest_distance[i] = INF;
        }
        q.push({x, weight[x]});
        while(!q.empty()){
            pair<long long, long long> p = q.front();
            shortest_distance[p.first] = min(p.second, shortest_distance[p.first]);
            hasVisited[p.first] = true;
            q.pop();
            for(int i: adj[p.first]){
                if(hasVisited[i]) continue;
                q.push({i, p.second + weight[i]});
            }
        }
        return shortest_distance;
    }
};
void solve(){
    Graph myTree;
    int n;
    cin >> n;
    myTree.adj.resize(n);
    myTree.weight.resize(n);
    for(int i = 0; i < n; i++){
        cin >> myTree.weight[i];
    }
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        myTree.adj[u].push_back(v);
        myTree.adj[v].push_back(u);
    }
    vector<vector<long long>> cost(n);
    for(int i = 0; i < n; i++){
        cost[i] = myTree.bfs(i);
    }
    Tree t;
    t.adj = myTree.adj;
    t.read(n);
    long long myMax = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            long long x = t.leastCommonAncestor(i, j);
            if(x != 0) continue;
            long long ans = cost[x][i] + cost[x][j];
            myMax = max(ans - myTree.weight[x], myMax);
        }
    }
    cout << myMax;
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        cout << "Case #" << i + 1 << ": ";
        solve();
        if(i != t - 1){
            cout << "\n";
        }
    }
}
