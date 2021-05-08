#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void put(string s){
    cout << s << '\n';
}
void put(int i){
    cout << i << '\n';
}
int n, a, b, da, db;
struct tree{
    vector<vector<int>> adj;
    vector<int> dist(int src){
        vector<int> v(adj.size());
        for(int i = 0; i < adj.size(); i++){
            v[i] = -1;
        }
        v[src] = 0;
        queue<pair<int,int>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            pair<int,int> p = pq.front();
            pq.pop();
            for(int i: adj[p.second]){
                if(v[i] == -1){
                    pq.push(make_pair(p.first + 1, i));
                    v[i] = p.first + 1;
                }
            }
        }
        return v;
    }
    int pnt(int A){
        vector<int> v = dist(A);
        int myMax = 0;
        int ind = 0;
        for(int i = 0; i < v.size(); i++){
            if(v[i] > myMax){
                ind = i;
                myMax = v[i];
            }
        }
        return ind;
    }
    int diameter(){
        return dist(pnt(pnt(0)))[pnt(0)];
    }
};
void solve(){
    cin >> n >> a >> b >> da >> db;
    a--, b--;
    tree t;
    t.adj.resize(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v);
        t.adj[v].push_back(u);
    }
    vector<int> dist = t.dist(a);
    if(dist[b] <= da || 2 * da >= db || 2 * da >= t.diameter()){
        put("Alice");
        return;
    }
    put("Bob");
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
