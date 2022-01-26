#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>
#include <random>
#include <array>
#include <chrono>

using namespace std;

void compress (vector<int> &v) {
    vector<int> vec;
    int prev = -1;
    for (int i = 0; i < v.size(); i++) {
        if (prev == v[i]) {
            continue;
        }
        vec.push_back(v[i]);
        prev = vec.back();
    }
    v = vec;
}

void solve() {
    int N;
    cin >> N;
    vector<vector<int>> arr(N);
    vector<int> large, small;
    int sz = 0;
    map<int, int> id;
    int cntr = 0;
    for (int i = 0; i < N; i++) {
        int n;
        cin >> n;
        sz += n;
        arr[i].resize(n);
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (!id.count(x)) {
                id[x] = cntr++;
            }
            arr[i][j] = id[x];
        }
        sort(arr[i].begin(), arr[i].end());
        compress(arr[i]);
    }
    int sq = 400;
    for (int i = 0; i < N; i++) {
        if (arr[i].size() >= sq) {
            large.push_back(i);
        } else {
            small.push_back(i);
        }
    }
    /*
     * 1) SMALL and SMALL
     * 2) LARGE and LARGE
     * 3) SMALL and LARGE
     */
    //LARGE AND LARGE
    vector<bool> w(cntr);
    for (int i1: large) {
        for (int j: arr[i1]) {
            w[j] = true;
        }
        for (int i2 = 0; i2 < N; i2++) {
            if (i2 == i1) continue;
            int c = 0;
            for (int j: arr[i2]) {
                if (w[j]) {
                    c++;
                }
            }
            if (c >= 2) {
                cout << i1 + 1 << " " << i2 + 1 << '\n';
                return;
            }
        }
        for (int j: arr[i1]) {
            w[j] = false;
        }
    }
    //SMALL AND SMALL
    vector<vector<int>> oc(cntr);
    for (int i: small) {
        for (int j: arr[i]) {
            oc[j].push_back(i);
        }
    }
    vector<vector<pair<int,int>>> ind(cntr);
    for (int i: small) {
        for (int j: arr[i]) {
            for (int k: arr[i]) {
                if (j >= k) continue;
                ind[j].push_back({k, i});
            }
        }
    }
    for (int i = 0; i < ind.size(); i++) {
        sort(ind[i].begin(), ind[i].end());
        for (int j = 1; j < ind[i].size(); j++) {
            if (ind[i][j].first == ind[i][j - 1].first) {
                cout << ind[i][j].second + 1 << " " << ind[i][j - 1].second + 1 << '\n';
                return;
            }
        }
    }
    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        solve();
    }
}
