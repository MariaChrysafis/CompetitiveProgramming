#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    dsu d;
    d.n = n;
    d.fill();
    map<int,vector<pair<int,int>>> myMap;
    vector<pair<int,pair<int,int>>> vec;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        myMap[w].emplace_back(u, v);
    }
    sort(vec.begin(), vec.end());
    vector<vector<int>> adj(n);
    int cntr = 0;
    for (auto& q: myMap) {
        vector<pair<int,int>> edges = q.second;
        for (auto& p: edges) {
            if (d.comp(p.first, p.second)) {
                cntr--;
            }
        }
        for (auto& p: edges) {
            if (!d.comp(p.first, p.second)) {
                d.join(p.first, p.second);
            } else {
                cntr++;
            }
        }
    }
    cout << cntr << '\n';
}
