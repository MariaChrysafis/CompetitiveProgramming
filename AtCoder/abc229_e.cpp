#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int components;
    int n;
    void fill (int N){
        n = N;
        components = N;
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
        components--;
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    dsu d;
    d.fill(N);
    vector<int> v;
    for (int i = N - 1; i >= 0; i--) {
        for (int j: adj[i]) {
            if (j >= i) {
                d.join(i, j);
            }
        }
        v.push_back(-i + d.components);
    }
    v.pop_back();
    reverse(v.begin(), v.end());
    for (int i: v) {
        cout << i << '\n';
    }
    cout << 0 << '\n';

}
