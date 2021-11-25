#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
void solve () {
    int N, K;
    cin >> N >> K;
    vector<int> x(K);
    for (int i = 0; i < K; i++) {
        cin >> x[i];
        x[i]--;
    }
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    queue<pair<int,int>> q;
    vector<bool> hasVisited;
    hasVisited.assign(N, false);
    map<int,vector<int>> myMap;
    for (int i = 0; i < K; i++) {
        q.push({x[i], 0});
    }
    vector<int> dist(N);
    while(!q.empty()) {
        int curNode = q.front().first;
        int curDist = q.front().second;
        q.pop();
        if (hasVisited[curNode]) {
            continue;
        }
        hasVisited[curNode] = true;
        dist[curNode] = curDist;
        myMap[curDist].push_back(curNode);
        for (int i: adj[curNode]) {
            q.push({i, curDist + 1});
        }
    }
    hasVisited.assign(N, false);
    q.push({0, 0});
    vector<int> distFromRoot(N); //depth
    map<int,vector<int>> myMapRoot;
    while(!q.empty()) {
        int curNode = q.front().first;
        int curDist = q.front().second;
        if (curNode != 0 && adj[curNode].size() == 1) {
            myMapRoot[curDist].push_back(curNode);
        }
        q.pop();
        if (hasVisited[curNode]) {
            continue;
        }
        hasVisited[curNode] = true;
        distFromRoot[curNode] = curDist;
        for (int i: adj[curNode]) {
            q.push({i, curDist + 1});
        }
    }
    set<int> visitable;
    for (int distance = 0; distance <= N; distance++) {
        for (int X: myMap[distance]) {
            visitable.insert(X);
        }
        for (int X: myMapRoot[distance]) {
            if (!visitable.count(X)) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
