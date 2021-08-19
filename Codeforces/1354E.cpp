#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
struct Graph{
    int n, m;
    int a, b, c;
    vector<int> coloring; //bipartite coloring
    vector<vector<int>> adj;
    vector<int> dum;
    vector<vector<int>> comp;
    void dfs(int cur, bool bol){
        comp.back().push_back(cur);
        coloring[cur] = bol;
        dum[bol]++;
        for(int i: adj[cur]){
            if(coloring[i] == -1){
                dfs(i, !bol);
            }
        }
    }
    void read(){
        cin >> n >> m;
        cin >> a >> b >> c;
        coloring.resize(n), adj.resize(n);
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v), adj[v].push_back(u);
        }
        for(int i = 0; i < n; i++){
            coloring[i] = -1;
        }
        dum = {0, 0};
        vector<vector<int>> v;
        for(int i = 0; i < n; i++){
            if(coloring[i] == -1){
                comp.push_back({});
                dfs(i, -1);
                v.push_back(dum);
                dum = {0, 0};
            }
        }
        for(int i = 0; i < n; i++){
            for(int j: adj[i]){
                if(coloring[i] == coloring[j]){
                    cout << "NO\n";
                    return;
                }
            }
        }
        vector<int> cur(n + 1);
        for(int i = 0; i <= n; i++) {
            cur[i] = 0;
        }
        vector<int> prev(n + 1);
        vector<vector<int>> taken(v.size());
        vector<vector<int>> dp;
        for(int i = 0; i < v.size(); i++){
            taken[i].resize(n + 1);
            for(int j = 0; j <= n; j++){
                taken[i][j] = -1;
            }
        }
        prev = cur;
        prev[0] = 1;
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j <= n; j++){
                bool pos1 = false;
                if(j - v[i][0] >= 0) {
                    if(prev[j - v[i][0]]){
                        taken[i][j] = 0;
                    }
                    pos1 |= prev[j - v[i][0]];
                }
                if(j - v[i][1] >= 0) {
                    if(prev[j - v[i][1]]){
                        taken[i][j] = 1;
                    }
                    pos1 |= prev[j - v[i][1]];
                }
                cur[j] = pos1;
            }
            dp.push_back(cur);
            prev = cur;
        }
        if(!cur[b]){
            cout << "NO\n";
            return;
        }
        string s;
        for(int i = 0; i < n; i++){
            s.push_back('?');
        }
        int soFar = b;
        vector<int> ans;
        for(int i = v.size() - 1; i >= 0; i--){
            if(taken[i][soFar] == 1){
                for(int x: comp[i]){
                    coloring[x] = !coloring[x];
                }
            }
            soFar -= v[i][taken[i][soFar]];
        }
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            if(coloring[i] == 0){
                s[i] = '2';
            } else if(a >= 1){
                s[i] = '1';
                a--;
            } else if (c >= 1){
                s[i] = '3';
                b--;
            }
        }
        cout << s << endl;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Graph g;
    g.read();
 
 
}
