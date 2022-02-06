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
int64_t MOD;

vector<int64_t> d;
int z = 0;

void red (int64_t& x) {
	if (x < 0) {
		x = (MOD - (-x)) % MOD;
	} else {
		x %= MOD;
	}
}

void update (int ind, int64_t val) {
	red(val);
	z -= (d[ind] == 0);
	d[ind] += val; d[ind] %= MOD;
	z += (d[ind] == 0);
}

int main() {
	ios_base::sync_with_stdio(0);
  	cin.tie(0);
	int n, q;
	cin >> n >> q;
	cin >> MOD;
	vector<int64_t> fib(n + 3);
	fib[0] = 0; fib[1] = 1;
	for (int i = 2; i < fib.size(); i++) {
		fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
	}
	int64_t a[n], b[n];
	for (int i = 0; i < n; i++) {
		int64_t x; cin >> x; 
		red(x);
		a[i] = x;
	}
	for (int i = 0; i < n; i++) {
		int64_t x; cin >> x; x = -x;
		red(x);
		a[i] += x, a[i] %= MOD;
	}
	d.assign(n, 0);
	z = n;
	update(0, a[0]);
	update(1, a[1] - a[0]);
	for (int i = 2; i < n; i++) {
		update(i, a[i] - a[i - 1] - a[i - 2]);
	}
	while (q--) {
		char c; cin >> c;
		int l, r; cin >> l >> r; l--, r--;
		int m = -1; if (c == 'A') m = 1;
		update(l, 1 * m);
		if (r + 1 < n) update(r + 1, -m * fib[r - l + 2]);
		if (r + 2 < n) update(r + 2, -m * fib[r - l + 1]);
		if (z == n) cout << "YES\n";
		else cout << "NO\n";
	}
}
