#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;

vector<ll> find_factors (int N) {
    vector<ll> ans;
    for (int i = 1; i < sqrt(N); i++) {
        if (N % i == 0) {
            ans.push_back(i), ans.push_back(N/i);
        }
    }
    int sq = sqrt(N);
    if (sq * sq == N) {
        ans.push_back(sq);
    }
    return ans;
}

int canPartition (vector<ll> arr, int MOD) {
    ll suf = 0;
    for (int i = 0; i < arr.size(); i++) {
        arr[i] %= MOD;
        suf += MOD - arr[i];
    }
    sort(arr.begin(), arr.end());
    ll pref = 0;
    ll ans = LLONG_MAX;
    for (int i = 0; i < arr.size(); i++) {
        pref += arr[i];
        suf -= MOD - arr[i];
        ans = min(ans, max(pref, suf));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K;
    cin >> N >> K;
    vector<ll> arr(N);
    ll sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        sum += arr[i];
    }
    //sum is up to 5 * 10^8
    vector<ll> factors = find_factors(sum);
    sort(factors.begin(), factors.end());
    reverse(factors.begin(), factors.end());
    for (ll x: factors) {
        if (canPartition(arr, x) <= K) {
            cout << x << '\n';
            return 0;
        }
    }
}
