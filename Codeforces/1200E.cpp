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
	ll res = x;
	ll ans = 1;
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
ll get (vector<ll> &pref, ll x, ll y) {
	ll res = (pref[y + 1] - mult(pref[x], binPow(base, y - x + 1)) + MOD) % MOD;
	return res;
}
void add (vector<ll>&pref, char c) {
	pref.push_back(mult(pref.back(), base) + (c - '0' + 1));
}
void remove (vector<ll>& pref) {
	pref.pop_back();
}
int main () {
	int N;
	cin >> N;
	vector<ll> pref = {0};
	string str;
	while (N--) {
		string s;
		cin >> s;
		vector<ll> new_pref = {0};
		for (char c: s) {
			add(new_pref, c);
		}
		bool done = false;
		int id = 0;
		for (int len = min(s.length(), pref.size() - 1); len >= 1; len--) {
			int en = pref.size() - 2;
			if (get(new_pref, 0, len - 1) == get(pref, en - len + 1, en)) {
				done = true;
				id = len;
				break;
			}
		}
		for (int i = 0; i < id; i++) {
			str.pop_back();
			remove(pref);
		}
		for (int i = 0; i < s.length(); i++) {
			str += s[i];
			add(pref, s[i]);
		}
	}
	cout << str;
}
