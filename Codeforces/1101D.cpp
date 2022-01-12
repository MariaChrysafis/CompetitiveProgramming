#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

int gcd (int x, int y) {
    if (!x || !y) return max(x, y);
    return gcd(max(x,y) % min(x,y), min(x,y));
}

const int MAX = 2e5 + 10;

vector<vector<int>> adj;
vector<int> depth;
vector<bool> hasVisited;
vector<int> mySet;

void dfs (int curNode, int prevNode) {
    hasVisited[curNode] = true;
    mySet.push_back(curNode);
    if (prevNode == -1) depth[curNode] = 1;
    else depth[curNode] = depth[prevNode] + 1;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs (i, curNode);
        }
    }
}

void reset () {
    for (int i: mySet) {
        hasVisited[i] = false;
    }
    mySet.clear();
}

int find_diameter (int head) {
    reset();
    dfs (head, -1);
    int best1 = 0;
    for (int i: mySet) {
        if (depth[i] > depth[best1]) {
            best1 = i;
        }
    }
    if (mySet.size() <= 2) {
        return mySet.size();
    }
    reset();
    dfs(best1, -1);
    int best2 = 0;
    for (int i: mySet) {
        if (depth[i] > depth[best2]) {
            best2 = i;
        }
    }
    return depth[best2];
}

vector<vector<int>> get_factors;
vector<bool> isPrime;
vector<int> primes;

void sieve () {
    get_factors.resize(MAX);
    isPrime.assign(MAX, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (isPrime[i]) {
            for (int j = 2 * i; j < MAX; j += i) {
                isPrime[j] = false;
            }
            primes.push_back(i);
        }
    }
    for (int i = 1; i < MAX; i++) {
        if (isPrime[i]) {
            for (int j = i; j < MAX; j += i) {
                get_factors[j].push_back(i);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int n;
    cin >> n;
    int g[n];
    depth.assign(n, 0);
    hasVisited.assign(n, false);
    vector<vector<int>> fact(MAX + 1);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
        for (int j: get_factors[g[i]]) {
            fact[j].push_back(i);
        }
    }
    adj.resize(n);
    vector<vector<pair<int,int>>> fact_edges(MAX);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int gc = gcd(g[u], g[v]);
        for (int j: get_factors[gc]) {
            fact_edges[j].push_back({u, v});
        }
    }
    int myMax = 0;
    for (int g: primes) {
        for (auto& p: fact_edges[g]) {
            adj[p.first].push_back(p.second);
            adj[p.second].push_back(p.first);
        }
        vector<int> heads;
        for (int i: fact[g]) {
            if (!hasVisited[i]) {
                dfs(i, -1);
                heads.push_back(i);
            }
        }
        reset();
        for (int i: heads) {
            myMax = max(myMax, find_diameter(i));
        }
        reset();
        for (int i: fact[g]) {
            adj[i].clear();
        }
    }
    cout << myMax;

}
