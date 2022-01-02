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

using namespace std;

typedef int64_t ll;
ll valid (ll X, vector<ll> v) {
    ll ans = 0;
    for (int i: v) {
        ll valA = (-i + (X + 1) * i) % (X + 1);
        ll valB = (i - valA * X)/(X + 1);
        if (valA >= 0 && valB >= 0) {
            ans += valA + valB;
        } else {
            return 1e12;
        }
    }
    return ans;
}
set<ll> factors (ll N) {
    set<ll> s;
    for (int i = 1; i <= sqrt(N); i++) {
        if (N % i == 0) {
            s.insert(i);
            s.insert(N/i);
        }
    }
    return s;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<ll> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    ll myMin = 1e12;
    for (int i = 31623; i >= 1; i--) {
        myMin = min(myMin, valid(i, v));
        int j = v[0]/i;
        if (j >= 0) myMin = min(myMin, valid(j, v));
        if (j - 1 >= 0) myMin = min(myMin, valid(j - 1, v));
        if (j + 1 >= 0) myMin = min(myMin, valid(j + 1, v));
    }
    cout << myMin << '\n';

}
