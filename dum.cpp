#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;
int n, k;
vector<vector<int>> pos;
void brute (vector<int> v) {
    if (v.size() == (n - 1) * (n - 1)) {
        pos.push_back(v);
        return;
    }
    for (int i = 1; i <= k; i++) {
        v.push_back(i);
        brute(v);
        v.pop_back();
    }
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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    brute({});
    int tot = 0;
    for (auto& v: pos) {
        vector<vector<int>> adj(n);
        vector<pair<int,pair<int,int>>> edges;
        int cntr = 0;
        for (int i = 0; i < n; i++) {
            adj[i].resize(n);
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    adj[i][j] = 0;
                    continue;
                }
                adj[i][j] = v[cntr++];
                edges.push_back({adj[i][j], {i, j}});
            }
        }
        dsu d;
        d.n = n;
        d.fill();
        sort(edges.begin(), edges.end());
        int ans = 0;
        for (auto& p: edges) {
            if (d.comp(p.second.first, p.second.second)) {
                continue;
            }
            d.join(p.second.first, p.second.second);
            ans += p.first;
        }
        int sm = 0;
        for (int i: adj[0])  {
            sm += i;
        }
        //cout << sm << " " << ans << '\n';
        if (sm == ans) tot++;
    }
    cout << tot;
}
