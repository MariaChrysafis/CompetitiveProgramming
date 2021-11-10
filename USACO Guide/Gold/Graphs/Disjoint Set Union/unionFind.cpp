#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll long long
#include <map>

using namespace std;
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int cc;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        cc = n;
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
        cc--;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    dsu d;
    int N, Q;
    cin >> N >> Q;
    d.n = N;
    d.fill();
    while(Q--) {
        int t;
        cin >> t;
        int u, v;
        cin >> u >> v;
        if (t == 0) {
            d.join(u, v);
        } else {
            cout << (d.find_head(u) == d.find_head(v)) << '\n';
        }
    }
}
