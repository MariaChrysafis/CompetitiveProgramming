#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef int64_t ll;

int N;

struct Node {
    bool inNode;
    bool outNode;
    int node;
    int weight;

    bool operator<(const Node &x) const {
        if (x.node != node) return (x.node < node);
        if (x.weight != weight) return (x.weight < weight);
        if (x.inNode != inNode) return (x.inNode < inNode);
        if (x.outNode != outNode) return (x.outNode < outNode);
        return false;
    }
};

map<Node, int> id;

vector<pair<int, int>> adj[1000000];
set<int> s;

const int INF = 1e9;

void dijk(int src) {
    int dist[1000000];
    int mark[1000000];
    for (int i: s) {
        dist[i] = INF;
        mark[i] = false;
    }
    Node st = {false, false, src, 0};
    dist[id[st]] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({0, id[st]});
    while (!pq.empty()) {
        int u = pq.top().second; //node
        pq.pop();
        if (mark[u]) {
            continue;
        }
        mark[u] = true;
        for (auto& p: adj[u]) {
            int v = p.second;
            int w = p.first;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({-dist[v], v});
            }
        }
    }
    for (int i = 0; i < N; i++) {
        Node cur = {false, false, i, 0};
        int x = dist[id[cur]];
        if (x == INF) {
            cout << "-1 ";
        } else {
            cout << x << ' ';
        }
    }
}

void add(Node x, Node y, int w) {
    //cout << x.inNode << " " << x.outNode << " " << x.node << " " << x.weight << " " << x.id() << '\n';
    if (!id[x]) {
        id[x] = s.size() + 1;
        s.insert(id[x]);
    }
    if (!id[y]) {
        id[y] = s.size() + 1;
        s.insert(id[y]);
    }
    adj[id[x]].push_back({w, id[y]});
}

int main() {
    int M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> inp(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        inp[u].push_back({w, v}), inp[v].push_back({w, u});
    }
    for (int i = 0; i < N; i++) {
        s.insert({false, false, i, 0});
    }
    for (int i = 0; i < N; i++) {
        set<int> pos_weights;
        for (auto &p: inp[i]) {
            pos_weights.insert(p.first);
        }
        for (int x: pos_weights) {
            for (int y: pos_weights) {
                Node in_node = {true, false, i, x};
                Node out_node = {false, true, i, y};
                add(in_node, out_node, (x + y) * (x + y));
            }
        }
        for (auto &p: inp[i]) {
            Node cur = {false, false, p.second, 0};
            Node in_node = {true, false, i, p.first};
            Node out_node{false, true, i, p.first};
            add(cur, in_node, 0);
            add(out_node, cur, 0);
        }
    }
    dijk(0);
}
