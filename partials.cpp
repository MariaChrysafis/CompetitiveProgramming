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
	x %= MOD, y %= MOD;
	return (x * y) % MOD;
}

ll add (ll x, ll y, int MOD) {
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
	return binPow(x, MOD - 2, MOD);
}

set<pair<ll,ll>> get_substring_hash (string s) {
	set<pair<ll,ll>> mySet;
	for (int i = 0; i < s.length(); i++) {
		vector<pair<ll,ll>> v = {{0, 0}};
		string pref;
		for (int j = i; j < s.length(); j++) {
			pref += s[j];
			pair<ll, ll> prev = v.back();
			v.emplace_back();
			v.back().first = mult(prev.first, base, MOD1) + (s[j] - 'a' + 1);
			v.back().second = mult(prev.second, base, MOD2) + (s[j] - 'a' + 1);
			v.back().first %= MOD1, v.back().second %= MOD2;
		}
		for (pair<ll,ll> x: v) {
			mySet.insert(x);
		}
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
    vector<set<pair<ll,ll>>> tot;
    map<pair<ll,ll>,ll> oc;
    for (int i = 0; i < arr.size(); i++) {
    	tot.push_back(get_substring_hash(arr[i]));
    	for (pair<ll,ll> x: tot.back()) {
    		oc[x]++;
    	}
    }
    for (int i = 0; i < tot.size(); i++) {
    	int ans = 0;
    	for (pair<ll,ll> x: tot[i]) {
    		if (oc[x] == 1) {
    			ans++;
    		}
    	}
    	cout << ans << '\n';
    }
}
