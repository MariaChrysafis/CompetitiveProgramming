#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int N;
    void fill(){
        parent.resize(N), compSize.resize(N);
        for(int i = 0; i < N; i++){
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
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    dsu g;
    cin >> g.N;
    g.fill();
    int M;
    cin >> M;
    vector<vector<int>> adj(g.N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> v(g.N);
    for (int i = 0; i < g.N; i++) {
        cin >> v[i];
        v[i]--;
    }
    set<int> s;
    reverse(v.begin(), v.end());
    vector<string> ans;
    for (int i = 0; i < v.size(); i++) {
        s.insert(v[i]);
        for (int j: adj[v[i]]) {
            if (s.count(j)) {
                g.join(v[i], j);
            }
        }
        bool b = (g.compSize[g.find_head(v[i])] == i + 1);
        //cout << b << endl;
        if (b) {
            //cout << "YES\n";
            ans.push_back("YES");
        } else {
            //cout << "NO\n";
            ans.push_back("NO");
        }
    }
    reverse(ans.begin(), ans.end());
    for (string str: ans) {
        cout << str << endl;
    }
}
