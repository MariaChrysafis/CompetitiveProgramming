#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
vector<int> generate(int i, int n){
    //cyclically shift [n] i times to the right
    vector<int> v(n);
    for(int j = 0; j < n; j++){
        v[j] = (i + j) % n;
    }
    return v;
}
struct Graph{
    vector<vector<int>> adj;
    vector<int> color;
    void add_edge(int u, int v){
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void dfs(int u, int col){
        //cout << u << endl;
        color[u] = col;
        for(int v: adj[u]){
            if(color[v] == -1){
                dfs(v, col);
            }
        }
    }
    int connectedComponents(){
        color.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            color[i] = -1;
        }
        int cntr = 0;
        for(int i = 0; i < adj.size(); i++){
            if(color[i] == -1) dfs(i, cntr), cntr++;
        }
        return cntr;
    }
    void read(int n){
        adj.resize(n);
    }
};
int minNumberOfSwaps(vector<int> v1, vector<int> v2){
    Graph g;
    g.read(v1.size());
    for(int i = 0; i < v1.size(); i++){
        g.add_edge(v1[i], v2[i]);
    }
    return v1.size() - g.connectedComponents();
}
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
        v[i]--;
    }
    vector<int> vec;
    for(int i = 0; i < n; i++){
        vec.push_back((v[i] - i + n) % n);
    }
    map<int,int> oc;
    for(int i: vec){
        oc[i]++;
    }
    vector<int> ans;
    for(int i = 0; i < n; i++){
        if(n - oc[i] <= 2 * m){
            //cout << i << " ";
            int swaps = minNumberOfSwaps(generate(i, n), v);
            if(swaps <= m){
                ans.push_back(i);
            }
        }
    }
    cout << ans.size() << " ";
    for(int i = 0; i < ans.size(); i++){
        ans[i] = (n - ans[i]) % n;
    }
    sort(ans.begin(), ans.end());
    print(ans);
    //cout << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
