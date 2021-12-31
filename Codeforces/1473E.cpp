#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

const ll INF = 1e15;

struct State {
    int curNode;
    bool _max;
    bool _min;

    bool operator<(const State &s1) const {
        if (s1.curNode != curNode) {
            return (s1.curNode < curNode);
        }
        if (s1._min != _min) {
            return (s1._min < _min);
        }
        if (s1._max != _max) {
            return (s1._max < _max);
        }
        return false;
    }
};

struct graph {
    vector<pair<State, ll>> adj[(int)2e5][2][2]; //{-weight, node}
    ll dist[(int)2e5][2][2];
    bool mark[(int)2e5][2][2];
    int N;
    void set (State& s, bool b) {
        mark[s.curNode][s._max][s._min] = b;
    }
    ll find_dist (State& s) {
        return dist[s.curNode][s._max][s._min];
    }
    void dijk(int src) {
        for (int i = 0; i < N; i++) {
            for (bool j: {true, false}) {
                for (bool k: {true, false}) {
                    State s = {i, j, k};
                    dist[i][j][k] = INF;
                    set(s, false);
                }
            }
        }
        dist[src][false][false] = 0;
        priority_queue<pair<ll, State>> pq;
        pq.push({0, {src, false, false}});
        while (!pq.empty()) {
            State myState = pq.top().second;
            pq.pop();
            if (mark[myState.curNode][myState._max][myState._min]) {
                continue;
            }
            set(myState, true);
            for (auto &p: adj[myState.curNode][myState._max][myState._min]) {
                State nextState = p.first;
                ll w = p.second;
                if (find_dist(myState) + w < find_dist(nextState)) {
                    dist[nextState.curNode][nextState._max][nextState._min] = find_dist(myState) + w;
                    pq.push({-find_dist(nextState), nextState});
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    graph g;
    int n, m;
    cin >> n >> m;
    g.N = n;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        for (bool b1: {true, false}) {
            for (bool b2: {true, false}) {
                for (bool b3: {true, false}) {
                    for (bool b4: {true, false}) {
                        if (!b3 && b1) continue;
                        if (!b4 && b2) continue;
                        if (!b1 && b3 && !b2 && b4) {
                            g.adj[u][b1][b2].push_back({{v, b3, b4}, w});
                            g.adj[v][b1][b2].push_back({{u, b3, b4}, w});
                            continue;
                        }
                        if (!b1 && b3) {
                            g.adj[u][b1][b2].push_back({{v, b3, b4}, 0});
                            g.adj[v][b1][b2].push_back({{u, b3, b4}, 0});
                        } else if (!b2 && b4) {
                            g.adj[u][b1][b2].push_back({{v, b3, b4}, 2 * w});
                            g.adj[v][b1][b2].push_back({{u, b3, b4}, 2 * w});
                        } else if (b1 == b3 && b2 == b4) {
                            g.adj[u][b1][b2].push_back({{v, b3, b4}, w});
                            g.adj[v][b1][b2].push_back({{u, b3, b4}, w});
                        } else {
                            assert(false);
                        }
                    }
                }
            }
        }
    }
    g.dijk(0);
    for (int i = 1; i < n; i++) {
        cout << g.dist[i][1][1] << ' ';
    }

}
