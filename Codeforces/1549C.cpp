#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <map>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void print(vector<long long> v){
    for(long long i: v){
        cout << i << " ";
    }
    cout << endl;
}
int gcd(int a, int b){
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
void solve(){
    int n, m;
    cin >> n >> m;
    vector<set<int>> adj(n);
    vector<bool> val(n);
    int cntr = 0;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    for(int i = 0; i < n; i++){
        if(adj[i].size() == 0 || *(--adj[i].end()) < i){
            cntr++;
            val[i] = true;
        }else{
            val[i] = false;
        }
    }
    //cout << cntr << endl;
    int q;
    cin >> q;
    //cout << q << endl;
    while(q--){
        int t;
        cin >> t;
        if(t == 3){
            cout << cntr << endl;
        }else if(t == 2){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].erase(v);
            adj[v].erase(u);
            vector<int> ans = {u, v};
            for(int x: ans) {
                if (adj[x].size() == 0 || *(--adj[x].end()) < x) {
                    if (!val[x]) {
                        val[x] = true;
                        cntr++;
                    }
                }
            }
        }else{
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].insert(v);
            adj[v].insert(u);
            vector<int> ans = {u, v};
            for(int x: ans) {
                if (adj[x].size() != 0 && *(--adj[x].end()) > x) {
                    if (val[x]) {
                        val[x] = false;
                        cntr--;
                    }
                }
            }
        }
    }
}
int main(){
    solve();
}
