#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int n;
    void fill (int N) {
        n = N;
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
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};

const int MAX = 1e6 + 5;

vector<vector<int>> fact;

void print (vector<int> v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}

void sieve () {
    fact.resize(MAX);
    for (int i = 2; i < fact.size(); i++) {
        if (fact[i].empty()) {
            for (int j = i; j < fact.size(); j += i) {
                fact[j].push_back(i);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N);
    dsu d1;
    d1.fill(MAX);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        for (int j: fact[a[i]]) {
            for (int k: fact[a[i]]) {
                d1.join(j, k);
                //cout << j << " <-> " << k << '\n';
            }
        }
    }
    map<pair<int,int>, bool> myMap;
    for (int i = 0; i < N; i++) {
        for (int j: fact[a[i]]) {
            for (int k: fact[a[i] + 1]) {
                myMap[{d1.find_head(j), d1.find_head(k)}] = myMap[{d1.find_head(k), d1.find_head(j)}] = true;
            }
        }
        for (int j: fact[a[i] + 1]) {
            for (int k: fact[a[i] + 1]) {
                myMap[{d1.find_head(j), d1.find_head(k)}] = myMap[{d1.find_head(k), d1.find_head(j)}] = true;
            }
        }
    }
    while (Q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int ans = 2;
        for (int j: fact[a[u]]) {
            for (int k: fact[a[v]]) {
                if (d1.comp(j, k)) {
                    ans = min(ans, 0);
                }
                if (myMap[{d1.find_head(j), d1.find_head(k)}]) {
                    ans = min(ans, 1);
                }
            }
        }
        cout << ans << '\n';
    }
}
