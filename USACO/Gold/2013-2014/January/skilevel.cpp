#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
vector<bool> starting;
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    vector<long long> start;
    int N;
    void fill(){
        parent.resize(N), compSize.resize(N), start.resize(N);
        for(int i = 0; i < N; i++){
            parent[i] = i, compSize[i] = 1;
            if (starting[i]) start[i] = starting[i];
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y) {
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        start[y] += start[x];
    }
};
vector<int> grid;
vector<vector<pair<int,int>>> adj;
int T;
int main() {
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M >> T;
    grid.resize(N * M);
    for (int i = 0; i < N * M; i++) {
        cin >> grid[i];
    }
    starting.resize(N * M);
    map<int,vector<pair<int,int>>> myMap;
    for (int i = 0; i < N * M; i++) {
        bool b;
        cin >> b;
        starting[i] = b;
    }
    adj.resize(N * M); //[node, weight]
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) != 1) {
                        continue;
                    }
                    if (dx + i < 0 || dx + i == N || dy + j < 0 || dy + j == M) {
                        continue;
                    }
                    int curNode = M * i + j;
                    int nxtNode = M * (i + dx) + (j + dy);
                    adj[curNode].push_back(make_pair(nxtNode, abs(grid[curNode] - grid[nxtNode])));
                    myMap[abs(grid[curNode] - grid[nxtNode])].push_back({curNode, nxtNode});
                }
            }
        }
    }
    dsu g;
    g.N = grid.size();
    g.fill();
    long long ans = 0;
    for (auto& pr: myMap) {
        vector<int> vis;
        for (pair<int,int>& p: pr.second) {
            p.first = g.find_head(p.first);
            p.second = g.find_head(p.second);
            int orig1 = g.compSize[p.first];
            int orig2 = g.compSize[p.second];
            if (orig1 >= T && orig2 >= T) {
                continue;
            }
            g.join(p.first, p.second);
            int x = g.find_head(p.first);
            int new1 = g.compSize[x];
            if (new1 < T) {
                continue;
            }
            if (orig1 < T && orig2 < T) {
                ans += pr.first * g.start[x];
                continue;
            }
            if (orig1 < T) {
                ans += pr.first * g.start[p.first];
            }
            if (orig2 < T) {
                ans += pr.first * g.start[p.second];
            }
        }
    }
    cout << ans;
}
