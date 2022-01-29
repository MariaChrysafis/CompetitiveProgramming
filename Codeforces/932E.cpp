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
const int base = 100;
const int MOD = 1e9 + 7;
ll mult (ll x, ll y) {
	return (x * y) % MOD;
}
ll binPow (ll x, ll y) {
	ll ans = 1;
	ll res = x;
	while (y > 0) {
		if (y & 1) {
			ans = mult(ans, res);
		}
		res = mult(res, res);
		y /= 2;
	}
	return ans;
}
ll inv (ll x) {
	return binPow(x, MOD - 2);
}
ll add (ll x, ll y) {
	return (x + y) % MOD;
}
ll combo (ll N, ll i) {
	ll ans = 1;
	for (ll x = N - i + 1; x <= N; x++) {
		ans = mult(ans, x);
	}
	return ans;
}
int main() {
	int N, K;
	cin >> N >> K;

	ll stirling[K + 1][K + 1];
	for (int i = 0; i <= K; i++) {
		for (int j = 0; j <= K; j++) {
			if (i == 0 || j == 0) {
				stirling[i][j] = (i == 0 && j == 0);
				continue;
			}
			stirling[i][j] = (stirling[i - 1][j] * j + stirling[i - 1][j - 1]) % MOD;
			stirling[i][j] %= MOD;
		}
	}
	ll ans = 0;
	for (int i = 1; i <= K; i++) {
		ll res = mult(stirling[K][i], binPow(2, N - i));
		res = mult(res, combo(N, i));
		ans = add(ans, res);
	}
	cout << ans;
}
