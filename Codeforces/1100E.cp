#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;
vector<vector<pair<int,int>>> tot_adj;
struct Graph {
    int n;
    Graph(int w) {
        adj.clear(), toPlace.clear();
        n = tot_adj.size();
        adj.resize(n);
        toPlace.resize(n);
        for (int i = 0; i < n; i++) {
            for (auto& p: tot_adj[i]) {
                if (p.second > w) {
                    //cout << i + 1 << "->" << p.first + 1 << '\n';
                    adj[i].push_back(p.first);
                } else {
                    toPlace.emplace_back(i, p.first);
                }
            }
        }
    }

    bool topo () {
        vector<int> deg;
        deg.assign(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j: adj[i]) {
                deg[j]++;
            }
        }
        vector<bool> flag;
        flag.assign(n, false);
        vector<int> v;
        priority_queue<int> pq;
        for(int i = 0; i < n; i++){
            if(deg[i] == 0){
                pq.push(i);
            }
        }
        while(!pq.empty()){
            while(flag[pq.top()] == true){
                pq.pop();
            }
            int i = pq.top();
            pq.pop();
            if(deg[i] == 0 && flag[i] == false){
                flag[i] = true;
                v.push_back(i);
                for(int j: adj[i]){
                    deg[j]--;
                    if(deg[j] == 0) {
                        pq.push(j);
                    }
                }
            }
        }
        if (v.size() != adj.size()) {
            return false;
        }
        gr = v;
        return true;
    }

    vector<vector<int>> adj;
    vector<pair<int,int>> toPlace;
    vector<int> gr;

};

vector<pair<int,pair<int,int>>> edges;

bool okay (int w) {
    Graph g(w);
    return g.topo();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    tot_adj.resize(N);
    while (M--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        //cout << u << " " << v << " " << w << '\n';
        tot_adj[u].push_back({v, w});
        edges.push_back({w, {u, v}});
    }
    int l = 0;
    int r = 1e9;
    while (l < r) {
        int mid = l + (r - l)/2;
        if (okay(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    Graph g(l);
    g.topo();
    vector<int> gr = g.gr;
    vector<int> loc(N);
    for (int i = 0; i < gr.size(); i++) {
        loc[gr[i]] = i;
        //cout << gr[i] << ' ';
    }
    //cout << '\n';
    vector<int> vec;
    for (int i = 0; i < edges.size(); i++) {
        auto p = edges[i];
        if (loc[p.second.first] > loc[p.second.second]) {
            vec.push_back(i + 1);
        }
    }
    cout << l << " " << vec.size() << '\n';
    for (int i: vec) {
        cout << i << ' ';
    }
}
