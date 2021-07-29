#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
#include <iomanip>
 
#define ll long long
#define endl '\n'
 
using namespace std;
void print(vector<int> v){
    for(int i : v) cout << i << " ";
    cout << endl;
}
void print(vector<ll> v){
    for(ll i : v) cout << i << " ";
    cout << endl;
}
void print(vector<vector<int>> v){
    for(vector<int> vec: v) print(vec);
    cout << endl;
}
void print(vector<vector<ll>> v){
    for(vector<ll> vec: v) print(vec);
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
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};
const int MOD = 1e9 + 7;
int main() {
    int n, m;
    cin >> n >> m;
    dsu g;
    g.n = m + 2;
    g.fill();
    for(int i = 0; i <= m + 1; i++){
        g.parent[i] = i;
    }
    vector<int> ans;
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        int a,b;
        if(k == 2){
            cin >> a >> b;
        }else if(k == 1){
            cin >> a;
            b = m + 1;
        }
        int ha = g.find_head(a);
        int hb = g.find_head(b);
        if(ha != hb) {
            g.join(a, b);
            ans.push_back(i);
        }
    }
    ll pwr = 1;
    for(int i = 0; i < ans.size(); i++){
        pwr *= 2;
        pwr %= MOD;
    }
    cout << pwr << " " << ans.size() << endl;
    for(int i: ans) cout << i + 1 << " ";
    cout << endl;
}
