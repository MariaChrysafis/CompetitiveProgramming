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

set<pair<ll,ll>> get_substring_hash (string s) {
	set<pair<ll,ll>> mySet;
	pair<ll,ll> st = get_hash(s).back();
	for (int i = 0; i < s.length(); i++) {
		pair<ll,ll> cur = st;
		//cout << cur.first << " " << cur.second << '\n';
		mySet.insert(cur);
		for (int j = s.length() - 1; j >= i; j--) {
			//cout << cur.first << " " << cur.second << '\n';
			cur.first -= (s[j] - 'a' + 1), cur.second -= (s[j] - 'a' + 1);
			cur.first = mult(cur.first, inv(base, MOD1), MOD1);
			cur.second = mult(cur.second, inv(base, MOD2), MOD2);
			mySet.insert(cur);
		}
		st.first -= mult(s[i] - 'a' + 1, binPow(base, s.length() - i - 1, MOD1), MOD1);
		st.second -= mult(s[i] - 'a' + 1, binPow(base, s.length() - i - 1, MOD2), MOD2);
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
    vector<string> arr;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
    	cin >> arr[i];
    }
    map<pair<ll,ll>,ll> oc;
    for (int i = 0; i < arr.size(); i++) {
    	for (pair<ll,ll> x: get_substring_hash(arr[i])) {
    		oc[x]++;
    	}
    }
    for (int i = 0; i < N; i++) {
    	int ans = 0;
    	for (pair<ll,ll> x: get_substring_hash(arr[i])) {
    		if (oc[x] == 1) {
    			ans++;
    		}
    	}
    	cout << ans << '\n';
    }
}
