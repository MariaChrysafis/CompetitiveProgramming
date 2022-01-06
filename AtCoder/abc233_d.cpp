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

using namespace std;
typedef long long ll;
const ll MAX = 1e18;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K;
    cin >> N >> K;
    ll a[N];
    vector<ll> pref = {0};
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        pref.push_back(pref.back() + a[i]);
    }
    map<ll, ll> cnt;
    ll ans = 0;
    for (int i = 0; i <= N; i++) {
        ans += cnt[pref[i] - K];
        cnt[pref[i]]++;
    }
    cout << ans << '\n';
}
