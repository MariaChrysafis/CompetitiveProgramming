#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

using namespace std;
#define ll long long
int main() {
    freopen("taxi.in", "r", stdin);
    freopen("taxi.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<ll> v1, v2;
    ll res = 0;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        v1.push_back(x), v2.push_back(y);
        res += abs(x - y);
    }
    v1.push_back(M);
    v2.push_back(0);
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    for (int i = 0; i < v1.size(); i++) {
        res += abs(v1[i] - v2[i]);
    }
    cout << res;
}
