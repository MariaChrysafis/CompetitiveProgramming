#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;
const int MOD = (int)1e9 + 7;
long long mult (long long x, long long y) {
	return (x * y) % MOD;
}
long long binPow(long long x, long long y) {
	long long ans = 1;
	long long res = x;
	while (y > 0) {
		if (y & 1) {
			ans = mult(ans, res);
		}
		res = mult(res, res);
		y /= 2;
	}
	return ans;
}
void solve(){
	int n, m;
	cin >> n >> m;
	int cnt[m + 1];
	int arr[n];
	for (int i = 0; i <= m; i++) {
		cnt[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		cnt[arr[i]]++;
	}
	long long f[m + 1];
	long long g[m + 1];
	for (int i = 1; i <= m; i++) {
		int ans = 0;
		for (int j = i; j <= m; j += i) {
			ans += cnt[j];
		}
		f[i] = binPow(2, ans) - 1;
		g[i] = f[i];
	}
	for (int i = m; i >= 1; i--) {
		//cout << f[i] << " ";
		for (int j = 2 * i; j <= m; j += i) {
			g[i] -= g[j];
			g[i] += MOD;
			g[i] %= MOD;
		}
	}
	for (int i = 1; i <= m; i++) {
		cout << g[i] << " ";
	}
	cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}
