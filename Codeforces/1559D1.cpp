#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
 
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int x: v) cout << x << " ";
    cout << endl;
}
 
void print(vector<ll> v){
    for(ll x: v) cout << x << " ";
    cout << endl;
}
 
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};
void solve(){
    int n;
    int m[2];
    cin >> n >> m[0] >> m[1];
    dsu d[2];
    d[0].n = n, d[1].n = n;
    d[0].fill(), d[1].fill();
    for(int j = 0; j < 2; j++) {
        for (int i = 0; i < m[j]; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            d[j].join(u, v);
            d[j].join(v, u);
        }
    }
    vector<pair<int,int>> ans;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(d[0].find_head(i) != d[0].find_head(j) && d[1].find_head(i) != d[1].find_head(j)){
                d[0].join(i, j);
                d[1].join(i, j);
                ans.push_back({i, j});
            }
        }
    }
    cout << ans.size() << endl;
    for(pair<int,int> p: ans) cout << p.first + 1 << " " << p.second + 1 << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
