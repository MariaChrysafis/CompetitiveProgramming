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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K;
    cin >> N >> K;
    vector<ll> arr;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    map<ll,pair<ll,ll>> interval;
    map<ll,ll> oc;
    sort(arr.begin(), arr.end());
    for (int i = 0; i < N; i++) {
        if (!oc[arr[i]]) {
            interval[arr[i]].first = interval[arr[i]].second = i;
        } else {
            interval[arr[i]].second++;
        }
        oc[arr[i]]++;
    }
    ll pref[arr.size() + 1];
    pref[0] = 0;
    for (int i = 1; i <= arr.size(); i++) {
        pref[i] = pref[i - 1] + arr[i - 1];
    }
    ll cnt = 0;
    ll myMin = 1e18;
    for (auto& p: oc) {
        if (p.second >= K) {
            cout << 0;
            return 0;
        }
        ll l = interval[p.first].first;
        ll r = interval[p.first].second;
        ll left = pref[l];
        ll right = pref[arr.size()] - pref[r + 1];
        ll cost_left = -left + (p.first - 1) * l;
        ll cost_right = -(arr.size() - r - 1) * (p.first + 1) + right;
        if (r + 1 >= K) {
            myMin = min(myMin, cost_left + K - p.second);
        }
        if (arr.size() - l >= K) {
            myMin = min(myMin, cost_right + K - p.second);
        }
        myMin = min(myMin, cost_left + cost_right + K - p.second);
        cnt += p.second;
    }
    cout << myMin;

}
