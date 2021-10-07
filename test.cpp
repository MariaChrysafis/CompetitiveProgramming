#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O3")
using namespace std;
struct Graph {
    vector<int> path;
    vector<set<int>> oc;
    vector<string> adj;
    int N, K;
    void read() {
        cin >> N >> K;
        path.resize(N);
        oc.resize(K);
        for (int i = 0; i < N; i++) {
            cin >> path[i];
            path[i]--;
            oc[path[i]].insert(i);
        }
        for (int i = 0; i < K; i++) {
            string s;
            cin >> s;
            adj.push_back(s);
            //adj[i][i] = '1';
        }
        queue<pair<int,int>> pq;
        pq.push({0, 0});
        int dist[N];
        for (int i = 0; i < N; i++) {
            dist[i] = 1e9;
        }
        while (!pq.empty()) {
            int cur = pq.front().second;
            //cout << path[cur] << endl;
            int distance = pq.front().first;
            pq.pop();
            for (int i = 0; i < K; i++) {
                if (adj[path[cur]][i] == '1' && !oc[i].empty()) {
                    auto it = oc[i].upper_bound(cur);
                    if (it == oc[i].end()) {
                        it--;
                    }
                    if (distance + abs(*it - cur) < dist[*it]) {
                        pq.push({distance + abs(*it - cur) , *it});
                        dist[*it] = distance + abs(*it - cur);
                    }
                }
            }
        }
        int ans = dist[N - 1];
        if(ans == (int)1e9) {
            cout << -1 << endl;
            return;
        }
        cout << ans<< endl;
    }
};
int main() {
    //freopen("haha", "r", stdin);
    Graph g;
    g.read();
}
