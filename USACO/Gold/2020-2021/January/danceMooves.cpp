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
    vector<bool> hasVisited;
    vector<vector<int>> adj;
    vector<vector<int>> comp;

    void dfs(int u) {
        for (int i: adj[u]) {
            if (!hasVisited[i]) {
                hasVisited[i] = true;
                comp.back().push_back(i);
                dfs(i);
            }
        }
    }

    void read(vector<int> nxt) {
        hasVisited.resize(nxt.size());
        adj.resize(nxt.size());
        for (int i = 0; i < nxt.size(); i++) {
            adj[i].push_back(nxt[i]);
            hasVisited[i] = false;
        }
        for (int i = 0; i < nxt.size(); i++) {
            if (!hasVisited[i]) {
                comp.push_back({});
                dfs(i);
            }
        }
    }
};

int read() {
    int x;
    cin >> x;
    return x;
}

map<int, int> oc;
set<int> values;
vector<pair<int, int>> vec;

void add(set<pair<int, int>> s, int R) {
    for (auto p: s) {
        int i = p.first;
        if (p.second > R) continue;
        oc[i]++;
        values.insert(i);
    }
}

void remove(set<pair<int, int>> s, int R) {
    for (auto p: s) {
        int i = p.first;
        if (p.second > R) continue;
        oc[i]--;
        if (oc[i] == 0) {
            values.erase(i);
        }
    }
}

int main() {
    //freopen("haha", "r", stdin);
    long long N, K, M;
    cin >> N >> K >> M;
    for (int i = 0; i < K; i++) {
        vec.push_back({read() - 1, read() - 1});
    }
    vector<int> arr(N);
    vector<set<pair<int, int>>> pos(N);
    for (int i = 0; i < N; i++) {
        arr[i] = i;
        pos[i].insert({i, 0});
    }
    for (int i = 0; i < vec.size(); i++) {
        pair<int, int> p = vec[i];
        pos[arr[p.first]].insert({p.second, i + 1});
        pos[arr[p.second]].insert({p.first, i + 1});
        swap(arr[p.first], arr[p.second]);
    }
    vector<int> prev(N), next(N);
    for (int i = 0; i < N; i++) {
        next[arr[i]] = i;
        prev[i] = arr[i];
    }
    Graph g;
    g.read(next);
    int ans[N];
    for (int i = 0; i < g.comp.size(); i++) {
        int tail = g.comp[i][0];
        int head = g.comp[i][0];
        int loop = min(M / K, (long long) g.comp[i].size());
        if (loop == 0) {
            for (int j = 0; j < g.comp[i].size(); j++) {
                add(pos[g.comp[i][j]], M % K);
                ans[g.comp[i][j]] = values.size();
                remove(pos[g.comp[i][j]], M % K);
            }
            values.clear();
            continue;
        }
        for (int j = 0; j < loop; j++) {
            add(pos[tail], K);
            tail = next[tail];
        }
        tail = prev[tail];
        add(pos[next[tail]], M % K);
        ans[head] = values.size();
        remove(pos[next[tail]], M % K);
        while (head != prev[g.comp[i][0]]) {
            //cout << head << " " << tail << endl;
            remove(pos[head], K);
            head = next[head];
            tail = next[tail];
            add(pos[tail], K);
            add(pos[next[tail]], M % K);
            ans[head] = values.size();
            remove(pos[next[tail]], M % K);
        }
        values.clear();
        oc.clear();
    }
    for (int i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }
}
