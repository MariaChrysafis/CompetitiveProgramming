#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <set>
 
using namespace std;
struct triple{
    long long a, b, c;
};
struct Pair {
    long long neighbor, weight;
};
bool operator<(Pair a, Pair b){
    return a.weight < b.weight;
}
bool operator>(Pair a, Pair b){
    return a.weight > b.weight;
}
struct graph {
    long long n;
    long long m;
    long long k;
    vector<vector<Pair>> graph;
    vector<bool> hasVisited;
    void dfs(long long cur){
        hasVisited[cur] = true;
        for(Pair p: graph[cur]){
            if(!hasVisited[p.neighbor]){
                dfs(p.neighbor);
            }
        }
    }
    bool isConnected(){
        hasVisited.clear();
        hasVisited.resize(n);
        for(int i = 0; i < n; i++){
            hasVisited[i] = false;
        }
        dfs(0);
        for(int i = 0; i < n; i++){
            if(!hasVisited[i]){
                return false;
            }
        }
        return true;
    }
    long long mst() {
        priority_queue<Pair, vector<Pair>, greater<Pair>> q; //smallest ones come first
        q.push({0, 0});
        bool added[graph.size()];
        for(int i = 0; i < graph.size(); i++){
            added[i] = false;
        }
        long long mst_cost = 0;
 
        while(!q.empty()) {
            Pair item;
            item = q.top();
            q.pop();
            long long node = item.neighbor;
            long long cost = item.weight;
            if(!added[node]) {
                added[node] = true;
                mst_cost += cost;
                for(auto & pair_cost_node : graph[node]) {
                    int adj_node = pair_cost_node.neighbor;
                    if(added[adj_node] == false) {
                        q.push(pair_cost_node);
                    }
                }
            }
        }
        return mst_cost;
    }
};
struct solve {
    graph g;
    vector<triple> inp;
    long long pos1(){
        for(int i = 0; i < g.n; i++) g.graph[i].clear();
        for(triple t: inp){
            if(t.c < g.k){
                g.graph[t.a].push_back({t.b, g.k - t.c});
                g.graph[t.b].push_back({t.a, g.k - t.c});
            }
        }
        long long ans = 1e15;
        if(g.isConnected()){
            for(triple t: inp){
                if(t.c < g.k){
                    ans = min(ans, g.k - t.c);
                }else{
                    ans = min(ans, t.c - g.k);
                }
            }
        }else {
            for (int i = 0; i < g.n; i++) g.graph[i].clear();
            for (triple t: inp) {
                g.graph[t.a].push_back({t.b, max(t.c - g.k, 0ll)});
                g.graph[t.b].push_back({t.a, max(t.c - g.k, 0ll)});
            }
            ans = min(ans, g.mst());
        }
        return ans;
    }
    void read() {
        cin >> g.n >> g.m >> g.k;
        g.graph.resize(g.n);
        for (int i = 0; i < g.m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            a--, b--;
            inp.push_back({a, b, c});
        }
        cout << pos1() << endl;
    }
};
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve s;
        s.read();
    }
}
