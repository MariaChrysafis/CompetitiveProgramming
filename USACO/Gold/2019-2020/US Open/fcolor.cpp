#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;
int N, M;
vector<vector<int>> adj;
vector<int> parent;
vector<vector<int>> children;
queue<int> q;
void merge(int u, int v) {
    if(u == v){
        return;
    }
    adj[u].insert(adj[u].begin(), adj[v].begin(), adj[v].end());
    adj[v].clear();
    parent[v] = u;
    for (int x : children[v]) {
        parent[x] = u;
        children[u].push_back(x);
    }
    if(adj[u].size() > 1){
        q.push(u);
    }
}
int main() {
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
    cin >> N >> M;
    adj.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        // all the cows adjacent to u have the same favorite color
    }
    parent.resize(N), children.resize(N);
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        children[i].push_back(i);
        if(adj[i].size() > 1){
            q.push(i);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        if(adj[x].size() <= 1){
            q.pop();
            continue;
        }
        int a = adj[x].back();
        adj[x].pop_back();
        merge(parent[a], parent[adj[x].back()]);
    }
    map<int,int> myMap;
    int oc = 1;
    for(int i = 0; i < N; i++){
        myMap[i] = -1;
    }
    for(int i = 0; i < N; i++){
        if(myMap[parent[i]] == -1){
            myMap[parent[i]] = oc;
            oc++;
        }
        cout << myMap[parent[i]] << endl;
    }
}
