#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<vector<int>> adj(n), inv_adj(n);
    for (int i = 0; i < n; i++) {
        if (i + v[i] < n) {
            adj[i].push_back(i + v[i]);
            inv_adj[i + v[i]].push_back(i);
        }
        if (i - v[i] >= 0) {
            adj[i].push_back(i - v[i]);
            inv_adj[i - v[i]].push_back(i);
        }
    }
    vector<int> fine;
    for (int i = 0; i < n; i++) {
        for (int j: adj[i]) {
            if (v[i] % 2 != v[j] % 2) {
                fine.push_back(i);
            }
        }
    }
    vector<int> dist;
    dist.assign(n, (int)1e9);
    queue<pair<int,int>> q;
    for (int i: fine) {
        dist[i] = 1;
        q.push({i, dist[i]});
    }
    while (!q.empty()) {
        int curNode = q.front().first;
        int curDist = q.front().second;
        q.pop();
        for (int i: inv_adj[curNode]) {
            if (dist[i] > curDist + 1) {
                q.push({i, curDist + 1});
                dist[i] = curDist + 1;
            }
        }
    }
    for (auto& i: dist) {
        if (i == (int)1e9) {
            i = -1;
        }
        cout << i << ' ';
    }
}
