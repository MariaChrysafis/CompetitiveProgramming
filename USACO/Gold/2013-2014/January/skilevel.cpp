#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
//#include <unordered_map>
#include <map>
using namespace std;
const int INF = 100000000;
vector<vector<int>> arr;
vector<vector<int>> strt;
struct coord {
    int x, y;
};
struct edge {
    int u, v;
    int weight;
};
int dist(coord c1, coord c2) { return abs(c1.x - c2.x) + abs(c1.y - c2.y); }
bool comp(edge e1, edge e2) { return e1.weight < e2.weight; }
vector<bool> marked;
int T;
vector<int> val;
edge e;
struct DSU {
    vector<int> parent;
    vector<int> rank;
    vector<int> connectedComponent;
    int n;
    int m;
    vector<vector<int>> members;
    void init() {
        parent.resize(n * m);
        rank.resize(n * m);
        marked.resize(n * m);
        members.resize(m * n);
        connectedComponent.resize(n * m);
        for (int i = 0; i < n * m; i++) {
            parent[i] = i;
            rank[i] = 0;
            marked[i] = false;
            connectedComponent[i] = 1;
            members[i].push_back(i);
        }
        // marked.resize(n);
    }
    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        return find_set(parent[v]);
    }
    void unite(int a, int b) {
        vector<int> v;
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b]) {
                swap(a, b);
            }
            parent[b] = a;
            members[a].insert(members[a].begin(), members[b].begin(),
                              members[b].end());
            members[b].clear();
            bool af = (connectedComponent[a] >= T);
            bool bf = (connectedComponent[b] >= T);
            connectedComponent[a] += connectedComponent[b];
            connectedComponent[b] = 0;
            if (rank[a] == rank[b]) {
                rank[a]++;
            }
            if (connectedComponent[a] < T) {
                members[a].insert(members[a].begin(), members[b].begin(),
                                  members[b].end());
                members[b].clear();
                return;
            }
            if (connectedComponent[a] >= T) {
                for(int x: members[a]){
                    val[x] = min(val[x], e.weight);
                }
                members[a].clear();
                    //val[a] = min(val[a], e.weight);
            }
            if (connectedComponent[b] >= T) {
                //val[b] = min(val[b], e.weight);
                for(int x: members[b]){
                    val[x] = min(val[x], e.weight);
                }
                members[b].clear();
            }
            members[a].insert(members[a].begin(), members[b].begin(),
                              members[b].end());
            members[b].clear();
        }
    }
};
int main() {
    ifstream in("skilevel.in");
    ofstream out("skilevel.out");
    int M, N;
    in >> M >> N >> T;
    arr.resize(M);
    strt.resize(M);
    for (int i = 0; i < M; i++) {
        arr[i].resize(N);
        strt[i].resize(N);
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            in >> arr[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            in >> strt[i][j];
        }
    }
    vector<edge> edges;
    vector<coord> step;
    step.push_back({1, 0});
    step.push_back({0, 1});
    // step.push_back({-1, 0});
    // step.push_back({0, -1});
    int id[M][N];
    coord rid[M * N];
    int c = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            id[i][j] = c;
            rid[c] = {i, j};
            c++;
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            coord cur = {i, j};
            coord nxt;
            for (int k = 0; k < step.size(); k++) {
                nxt = {cur.x + step[k].x, cur.y + step[k].y};
                if (nxt.x >= 0 && nxt.y >= 0 && nxt.x < M && nxt.y < N) {
                    int dist = arr[cur.x][cur.y] - arr[nxt.x][nxt.y];
                    edges.push_back(
                        {id[cur.x][cur.y], id[nxt.x][nxt.y], abs(dist)});
                }
            }
        }
    }
    sort(edges.begin(), edges.end(), comp);
    DSU dsu;
    dsu.n = N, dsu.m = M, dsu.init();
    val.resize(N * M);
    for (int i = 0; i < N * M; i++) {
        val[i] = INF;
    }
    for (int i = 0; i < edges.size(); i++) {
        e = edges[i];
        dsu.unite(edges[i].u, edges[i].v);
        //for (int j = 0; j < N * M; j++) {
            //if (dsu.connectedComponent[dsu.find_set(j)] >= T) {
                //val[j] = min(val[j], edges[i].weight);
            //}
        //}
    }
    long long sm = 0;
    for (int i = 0; i < N * M; i++) {
        if (strt[rid[i].x][rid[i].y] == 1) {
            sm += val[i];
        }
    }
    out << sm << endl;
}
