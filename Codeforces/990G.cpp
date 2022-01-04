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
#include <iomanip>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

typedef int64_t ll;

struct dsu{
    vector<ll> parent;
    vector<ll> compSize;
    ll n;
    ll ans = 0;
    void fill(){
        ans = 0;
        parent.resize(n), compSize.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
        }
        parent[x] = y;
        ans -= compSize[y] * (compSize[y] - 1)/2;
        ans -= compSize[x] * (compSize[x] - 1)/2;
        compSize[y] += compSize[x];
        ans += compSize[y] * (compSize[y] - 1)/2;
        compSize[x] = 0;
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};

const int MAX = 200005;
ll lpf[MAX], mu[MAX];
void lpf_sieve (int N) {
    for (int i = 2; i < N; i++) {
        if (!lpf[i]) {
            for (int j = i; j < N; j += i) {
                if (!lpf[j]) {
                    lpf[j] = i;
                }
            }
        }
    }
}

void mob_sieve (int N) {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (lpf[i/lpf[i]] == lpf[i]) {
            mu[i] = 0;
        } else {
            mu[i] = -1 * mu[i/lpf[i]];
        }
    }
}

void sieve (int N) {
    lpf_sieve(N);
    mob_sieve(N);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve(MAX);
    int n;
    cin >> n;
    vector<int> indices[MAX];
    int val[n];
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        indices[val[i]].push_back(i);
    }
    vector<int> adj[n];
    set<int> adjS[n];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        adjS[u].insert(v), adjS[v].insert(u);
    }
    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
    ll g[MAX];
    dsu d;
    d.n = n;
    d.fill();
    for (int i = 1; i < MAX; i++) {
        d.ans = 0;
        for (int j = i; j < MAX; j += i) {
            d.ans += indices[j].size();
        }
        for (int j = i; j < MAX; j += i) {
            for (int ind1: indices[j]) {
                if (d.ans <= 470) {
                    for (int k = i; k < MAX; k += i) {
                        for (int ind2: indices[k]) {
                            if (adjS[ind1].count(ind2)) {
                                d.join(ind1, ind2);
                            }
                        }
                    }
                } else {
                    for (int k: adj[ind1]) {
                        if (val[k] % i == 0) {
                            d.join(ind1, k);
                        }
                    }
                }
            }
        }
        g[i] = d.ans;
        for (int j = i; j < MAX; j += i) {
            for (int ind: indices[j]) {
                d.compSize[ind] = 1;
                d.parent[ind] = ind;
            }
        }
        d.ans = 0;
    }
    ll f[MAX];
    for (int i = 0; i < MAX; i++) {
        f[i] = 0;
    }
    for (int i = 1; i < MAX; i++) {
        for (int j = i; j < MAX; j += i) {
            f[i] += g[j] * mu[j/i];
        }
    }
    for (int i = 1; i < MAX; i++) {
        if (f[i]) {
            cout << i << " " << f[i] << '\n';
        }
    }
}
