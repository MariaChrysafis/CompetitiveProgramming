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
int main()  {
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> vec(m);
    vector<vector<int>> adj(n);
    vector<int> inDegree;
    inDegree.assign(n, 0);
    for (int i = 0; i < m; i++) {
        cin >> vec[i].first >> vec[i].second;
        vec[i].first--, vec[i].second--;
        adj[vec[i].first].push_back(vec[i].second);
        inDegree[vec[i].second]++;
    }
    priority_queue<int, std::vector<int>, std::greater<int> > pq;
    for (int i = 0; i < adj.size(); i++) {
        if (!inDegree[i]) {
            pq.push(i);
        }
    }
    vector<int> v;
    while (!pq.empty()) {
        int curNode = pq.top();
        pq.pop();
        v.push_back(curNode);
        for (int i: adj[curNode]) {
            inDegree[i]--;
            if (!inDegree[i]) {
                pq.push(i);
            }
        }
    }
    if (v.size() != n) {
        cout << -1;
        return 0;
    }
    for (int i: v) {
        cout << i + 1 << ' ';
    }
}
