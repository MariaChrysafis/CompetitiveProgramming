#include <iostream>
#include <vector>
#include "dreaming.h"
#include <climits>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
vector<int> a, b, w;
vector<vector<int> > adj;
map<pair<int,int>,int> myMap;
vector<bool> hasVisited;
vector<int> parent;
pair<int,int> find_farthest_node (int x, bool undo) {
    queue<pair<int,int> > q;
    q.push(make_pair(x, 0));
    hasVisited[x] = true;
    parent[x] = -1;
    vector<int> nodes;
    vector<pair<int,int> > vec;
    while (!q.empty()) {
        pair<int,int> p = q.front();
        nodes.push_back(p.first);
        vec.push_back(make_pair(p.second, p.first));
        q.pop();
        for (int j: adj[p.first]) {
            if (!hasVisited[j]) {
                q.push(make_pair(j, p.second + myMap[make_pair(j, p.first)]));
                parent[j] = p.first;
                hasVisited[j] = true;
            }
        }
    }
 
    if (undo) {
        for (int j: nodes) {
            hasVisited[j] = false;
        }
    }
    sort(vec.begin(), vec.end());
    return vec.back(); //first distance, then node
}
int travelTime (int N, int M, int L, int A[], int B[], int W[]) {
    a.resize(M), b.resize(M), w.resize(M), adj.resize(N), parent.resize(N);
    for (int i = 0; i < M; i++) {
        a[i] = A[i], b[i] = B[i], w[i] = W[i];
        myMap[make_pair(a[i], b[i])] = w[i];
        myMap[make_pair(b[i], a[i])] = w[i];
        adj[a[i]].push_back(b[i]), adj[b[i]].push_back(a[i]);
    }
    hasVisited.assign(N, false);
    vector<int> paths;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (!hasVisited[i]) {
            int x = find_farthest_node(i, true).second;
            int y = find_farthest_node(x, true).second;
            vector<int> nodes;
            int val = y;
            while (val != -1) {
                nodes.push_back(val);
                val = parent[val];
            }
            int sum = 0;
            for (int j = 1; j < (int) nodes.size(); j++) {
                sum += myMap[make_pair(nodes[j], nodes[j - 1])];
            }
            ans = max(ans, sum);
            int c = 0;
            int myMin = INT_MAX;
            int best = 0;
            for (int j = 1; j < (int)nodes.size(); j++) {
                c += myMap[make_pair(nodes[j], nodes[j - 1])];
                if (max(c, sum - c) < myMin) {
                    myMin = max(c, sum - c);
                    best = nodes[j];
                }
            }
            if (nodes.size() == 1) {
                myMin = 0;
            }
            paths.push_back(find_farthest_node(best, false).first);
        }
    }
    sort(paths.begin(), paths.end());
    //cout << paths.size() << '\n';
    if (paths.size() == 1) {
        ans = max(ans, paths[0]);
    } else if (paths.size() == 2) {
        ans = max(paths.back() + paths[paths.size() - 2] + L, ans);
    } else {
        ans = max(paths.back() + paths[paths.size() - 2] + 2 * L, ans);
    }
    return ans;
}
 
/*
int main() {
   int N = 12;
   int M = 8;
   int L = 2;
   int A[M], B[M], T[M];
   A[0] = 0, A[1] = 8, A[2] = 2, A[3] = 5, A[4] = 5, A[5] = 1, A[6] = 1, A[7] = 10;
   B[0] = 8, B[1] = 2, B[2] = 7, B[3] = 11, B[4] = 1, B[5] = 3, B[6] = 9, B[7] = 6;
   T[0] = 4, T[1] = 2, T[2] = 4, T[3] = 3, T[4] = 7, T[5] = 1, T[6] = 5, T[7] = 3;
   cout << travelTime(N, M, L, A, B, T);
}
*/
