#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<pair<ll,ll>> vec;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vec.emplace_back(a[i], i);
    }
    sort(vec.begin(), vec.end());
    vector<ll> close;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            close.push_back(i/2);
        } else {
            close.push_back((-i - 1)/2);
        }
    }
    reverse(close.begin(), close.end());
    vector<ll> ans(n + 1);
    ans[0] = 0;
    for (int i = 1; i <= n; i++) {
        ans[vec[i - 1].second + 1] = close[i - 1];
    }
    ll cntr = 0;
    for (int i = 1; i < ans.size(); i++) {
        cntr += abs(ans[i]) * a[i - 1];
    }
    cntr *= 2;
    cout << cntr << '\n';
    for (ll i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main()  {
        int t;
        cin >> t;
        while (t--) {
            solve();
        }
}
