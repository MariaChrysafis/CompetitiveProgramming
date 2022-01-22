#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

void solve () {
    int N, K;
    cin >> N >> K;
    vector<pair<int,int>> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first;
    }
    for (int i = 0;i < N; i++) {
        cin >> vec[i].second;
    }
    sort(vec.begin(), vec.end());
    int cur = K;
    for (int i = 0; i < N; i++) {
        if (cur >= vec[i].first) {
            cur += vec[i].second;
        }
    }
    cout << cur << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
