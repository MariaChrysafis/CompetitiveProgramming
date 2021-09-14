#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

template<typename T>
T readVal() {
    T n;
    cin >> n;
    return n;
}

template<typename T>
vector<T> readVector(T n) {
    vector<T> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

template<typename T>
void printVector(vector<T> vec) {
    for (T x: vec) {
        cout << x << " ";
    }
    cout << endl;
}

vector<int> color;
vector<bool> hasVisited;
vector<vector<int>> adj;
bool valid = true;

void dfs(int curNode, int col) {
    hasVisited[curNode] = true;
    color[curNode] = col;
    for (int i: adj[curNode]) {
        if (!hasVisited[i]) {
            dfs(i, !col);
        } else {
            if (color[i] != !col) {
                valid = false;
            }
        }
    }
}

pair<int,int> p;

bool detect_cycle(int node, int par)
{
    hasVisited[node] = true;
    for (int child : adj[node]) {
        if (!hasVisited[child]) {
            if (detect_cycle(child, node)) {
                return true;
            }
        }
        else if (child != par) {
            p.first = child;
            p.second = node;
            return true;
        }
    }
    return false;
}

vector<int> find_simple_cycle(int a, int b){
    vector<int> par(adj.size(), -1);
    vector<bool> vis(adj.size());
    for(int i = 0; i < adj.size(); i++){
        vis[i] = false;
    }
    queue<int> q;
    q.push(a);
    bool ok = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        vis[node] = true;
        for (int child : adj[node]) {
            if (node == a && child == b)
                continue;
            if (vis[child] == 0) {
                par[child] = node;
                if (child == b) {
                    ok = false;
                    break;
                }
                q.push(child);
                vis[child] = true;
            }
        }

        if (ok == false)
            break;
    }

    vector<int> simple_cycle;
    simple_cycle.push_back(a);
    int x = b;
    while (x != a) {
        simple_cycle.push_back(x);
        x = par[x];
    }
    return simple_cycle;
}

void solve() {
    int n = readVal<int>();
    int m = readVal<int>();
    int k = readVal<int>();
    color.resize(n);
    adj.resize(n);
    hasVisited.resize(n);
    for (int i = 0; i < n; i++) {
        hasVisited[i] = false;
    }
    while (m--) {
        int u = readVal<int>();
        int v = readVal<int>();
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    queue<int> q;
    q.push(0);
    hasVisited[0] = true;
    set<int> popped;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        popped.insert(x);
        if (popped.size() == k) {
            break;
        }
        for (int i: adj[x]) {
            if (!hasVisited[i]) {
                q.push(i);
                hasVisited[i] = true;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        hasVisited[i] = false;
    }
    vector<vector<int>> new_adj(n);
    for (int i = 0; i < n; i++) {
        if (!popped.count(i)) continue;
        for (int j: adj[i]) {
            if (!popped.count(j)) continue;
            new_adj[i].push_back(j);
        }
    }
    adj = new_adj;
    dfs(0, 0);
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    for (int i: popped) {
        cnt[color[i]]++;
    }
    if(valid) {
        int desCol = (cnt[0] < cnt[1]);
        vector<int> v;
        for (int i: popped) {
            if (color[i] == desCol) {
                v.push_back(i);
            }
        }
        cout << 1 << endl;
        for (int i = 0; i < (k + 1) / 2; i++) {
            cout << v[i] + 1 << " ";
        }
        cout << endl;
        return;
    }
    for(int i = 0; i < hasVisited.size(); i++){
        hasVisited[i] = false;
    }
    detect_cycle(0, -1);
    vector<int> v = find_simple_cycle(p.first, p.second);
    cout << 2 << endl;
    cout << v.size() << endl;
    for(int i: v){
        cout << i + 1 << " ";
    }
    cout << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
