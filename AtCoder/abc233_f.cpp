#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;
const ll MAX = 1e18;
bool sorted (vector<int> v) {
    vector<int> vec = v;
    sort(v.begin(), v.end());
    return (vec == v);
}
struct Entry {
    int curNode = -1;
    int prevNode = -1;
    int type = -1; //index of edge traversed
};
vector<int> ans;
vector<vector<pair<int,int>>> adj;
vector<int> deg;
set<int> forbidden;
void rec (vector<int> permutation) {
    if (sorted(permutation)) {
        return;
    }
    int src = -1;
    for (int i = 0; i < permutation.size(); i++) {
        if (deg[i] == 1 && i != permutation[i]) {
            src = i;
        }
        if (forbidden.count(i)) {
            assert(i == permutation[i]);
        }
    }
    if (src == -1) {
        for (int i = 0; i < permutation.size(); i++) {
            if (deg[i] == 1 && i == permutation[i]) {
                src = i;
                for (pair<int,int> p: adj[i]) {
                    if (!forbidden.count(p.first)) {
                        ans.push_back(p.second + 1);
                        swap(permutation[p.first], permutation[i]);
                    }
                }
                break;
            }
        }
    }
    /*
    cout << src << '\n';
    for (int j: permutation) {
        cout << j + 1 << " ";
    }
    cout << '\n';
    for (int j: deg) {
        cout << j << ' ';
    }
    cout << '\n';
    cout << '\n';
     */
    int ind = -1;
    for (int i = 0; i < permutation.size(); i++) {
        if (permutation[i] == src) {
            ind = i;
            break;
        }
    }
    if (ind == -1 || src == -1) {
        cout << "-1\n";
        exit(0);
    }
    queue<Entry> q;
    q.push({src, -1, -1});
    Entry dist[permutation.size()];
    int other = -1;
    while (!q.empty()) {
        Entry myEntry = q.front();
        q.pop();
        if (dist[myEntry.curNode].curNode != -1) {
            continue;
        }
        dist[myEntry.curNode] = myEntry;
        if (myEntry.curNode == ind) {
            break;
        }
        for (pair<int,int> p: adj[myEntry.curNode]) {
            if (!forbidden.count(p.first)) {
                if (myEntry.curNode == src) {
                    assert(other == -1);
                    other = p.first;
                }
                q.push({p.first, myEntry.curNode, p.second});
            }
        }
    }
    if (dist[ind].prevNode == -1) {
        cout << "-1";
        exit(0);
    }
    Entry e = dist[ind];
    while (e.prevNode != -1) {
        swap(permutation[e.curNode], permutation[e.prevNode]);
        ans.push_back(e.type + 1);
        e = dist[e.prevNode];
    }
    assert(permutation[src] == src);
    assert(other != -1);
    deg[src]--;
    deg[other]--;
    forbidden.insert(src);
    rec(permutation);
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
    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
        P[i]--;
    }
    dsu d;
    d.n = N;
    d.fill();
    int M;
    cin >> M;
    adj.resize(N);
    deg.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (d.find_head(u) == d.find_head(v)) {
            continue;
        }
        adj[u].push_back({v, i}), adj[v].push_back({u, i});
        d.join(u, v);
        //cout << u + 1 << " " << v + 1 << '\n';
    }
    for (int i = 0; i < N; i++) {
        deg[i] = adj[i].size();
    }
    rec(P);
    assert(ans.size() <= 5e5);
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }

}
