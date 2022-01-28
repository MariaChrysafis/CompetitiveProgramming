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

typedef int64_t ll;

void solve () {
    int N, K;
    cin >> N >> K;
    vector<pair<int,int>> v;
    vector<int> oc(N);
    for (int i = 0; i < N/2; i++) {
        v.push_back({i, N - i - 1});
        oc[i] = oc[N - i - 1] = i;
    }
    vector<vector<int>> ans;
    int ma = 0;
    for (auto& p: v) {
        ans.push_back({});
        vector<int> vec = {p.first, p.second};
        int ba = 0;
        for (int i: vec) {
            if (i == 0) ans.back().push_back(K);
            else if (i == K) ans.back().push_back(0);
            else ans.back().push_back(i);
        }
        ba = ans.back()[0] & ans.back()[1];
        ma += ba;
    }
    if (ma == K) {
        for (auto& vr: ans) {
            for (int i: vr) {
                cout << i << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
        return;
    }
    if (N == 4 && K == 3) {
        cout << "-1\n";
        return;
    }
    assert(K == N - 1);
    int lg2 = log2(N);
    set<int> forbidden = {0, 1, 3, N - 1, N - 2, N - 4};
    for (vector<int>& vr: ans) {
        if (forbidden.count(vr[0]) || forbidden.count(vr[1])) {
            continue;
        }
        cout << vr[0] << " " << vr[1] << '\n';
    }
    cout << 1 << " " << 3 << '\n';
    cout << N - 4 << " " << 0 << '\n';
    cout << N - 1 << " "<< N - 2<< '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
