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

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int base = 27;

ll mult (ll x, ll y, int MOD) {
	if (x < 0) x += MOD; if (y > 0) y += MOD;
	x %= MOD, y %= MOD;
	return (x * y) % MOD;
}

ll add (ll x, ll y, int MOD) {
	if (x < 0) x += MOD; if (y > 0) y += MOD;
	x %= MOD, y %= MOD;
	return (x + y) % MOD;
}

ll binPow (ll x, ll y, int MOD) {
	ll ans = 1;
	ll res = x;
	while (y > 0) {
		if (y & 1) {
			ans = mult(ans, res, MOD);
		}
		res = mult(res, res, MOD);
		y /= 2;
	}
	return ans;
}

ll inv (ll x, int MOD) {
	if (x < 0) {
		x += MOD;
	}
	return binPow(x, MOD - 2, MOD);
}

vector<pair<ll,ll>> get_hash (string s) {
	vector<pair<ll,ll>> v = {{0, 0}};
	for (int i = 0; i < s.size(); i++) {
		pair<ll, ll> prev = v.back();
		v.emplace_back();
		v.back().first = mult(prev.first, base, MOD1) + (s[i] - 'a' + 1);
		v.back().second = mult(prev.second, base, MOD2) + (s[i] - 'a' + 1);
		v.back().first %= MOD1, v.back().second %= MOD2;
	}
	return v;
}

vector<ll> powr1, powr2;
vector<ll> ipowr1, ipowr2;

set<pair<ll,ll>> get_substring_hash (string s) {
	set<pair<ll,ll>> mySet;
	pair<ll,ll> st = get_hash(s).back();
	for (int i = 0; i < s.length(); i++) {
		pair<ll,ll> cur = st;
		mySet.insert(cur);
		for (int j = s.length() - 1; j >= i; j--) {
			cur.first -= (s[j] - 'a' + 1), cur.second -= (s[j] - 'a' + 1);
			cur.first = mult(cur.first, ipowr1[1], MOD1);
			cur.second = mult(cur.second, ipowr2[1], MOD2);
			if (mySet.count(cur)) {
				break;
			}
			mySet.insert(cur);
		}
		st.first -= mult(s[i] - 'a' + 1, powr1[s.length() - i - 1], MOD1);
		st.second -= mult(s[i] - 'a' + 1, powr2[s.length() - i - 1], MOD2);
		st.first += MOD1, st.second += MOD2, st.first %= MOD1, st.second %= MOD2;
	}
	return mySet;
}

int main() {
	freopen("standingout.in", "r", stdin);
	freopen("standingout.out", "w", stdout);
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    powr1 = {1}, powr2 = {1};
    while (powr1.size() != N + 10) {
    	powr1.push_back(mult(powr1.back(), base, MOD1));
    	powr2.push_back(mult(powr2.back(), base, MOD2));
    }
    for (ll x: powr1) ipowr1.push_back(inv(x, MOD1));
    for (ll x: powr2) ipowr2.push_back(inv(x, MOD2));
    vector<string> arr;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
    	cin >> arr[i];
    }
    map<pair<ll,ll>,ll> oc;
    vector<set<pair<ll,ll>>> tot;
    for (int i = 0; i < arr.size(); i++) {
    	tot.emplace_back(get_substring_hash(arr[i]));
    	for (pair<ll,ll> x: tot.back()) {
    		oc[x]++;
    	}
    }
    for (int i = 0; i < N; i++) {
    	int ans = 0;
    	for (pair<ll,ll> x: tot[i]) {
    		if (oc[x] == 1) {
    			ans++;
    		}
    	}
    	cout << ans << '\n';
    }
}
