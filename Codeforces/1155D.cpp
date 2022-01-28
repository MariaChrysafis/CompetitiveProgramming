#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;

typedef int64_t ll;
void pos (int N, int X) {
	vector<ll> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	vector<ll> longest_pref(N), longest_suf(N);
	longest_pref[0] = max(arr[0], 0ll);
	for (int i = 1; i < N; i++) {
		longest_pref[i] = max(longest_pref[i - 1] + arr[i], arr[i]);
		longest_pref[i] = max(longest_pref[i], 0ll);
	}
	longest_suf[N - 1] = max(arr[N - 1], 0ll);
	for (int i = N - 2; i >= 0; i--) {
		longest_suf[i] = max(longest_suf[i + 1] + arr[i], arr[i]);
		longest_suf[i] = max(longest_suf[i], 0ll);
	}
	ll pref = 0;
	ll min_vl = 0;
	ll ans = 0;
	for (int i = 0; i < N; i++) {
		pref += arr[i];
		ll vr = X * pref + (i == N - 1 ? 0 : longest_suf[i + 1]);
		ll vl = X * pref - longest_pref[i];
		ans = max(ans, vr - min_vl);
		min_vl = min(min_vl, vl);
	}
	cout << max(ans, pref) << '\n';
}
int main() {
	ll N, X;
	cin >> N >> X;
	pos(N, X);
}
