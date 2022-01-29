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

vector<int> prefix_function(string& s) {
    vector<int> LPS(s.size());
    LPS[0] = 0;
    for (int i = 1; i < int(s.size()); i++) {
        int j = LPS[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = LPS[j - 1];
        }
        if (s[i] == s[j]) {
            LPS[i] = j + 1;
        }
        else {
            LPS[i] = 0;
        }
    }
    return LPS;
}

vector<int> count_occurrence(string& s) {
    int n = s.size();
    vector<int> LPS = prefix_function(s);
    vector<int> occ(n + 1);
    for (int i = 0; i < n; i++) {
        occ[LPS[i]]++;
    }
    for (int i = n - 1;
         i > 0; i--) {
        occ[LPS[i - 1]] += occ[i];
    }
    for (int i = 0; i <= n; i++) {
        occ[i]++;
    }
    return occ;
}

const int base = 29;

const int MOD = 1e9 + 7;

ll mult (ll x, ll y) {
	return (x * y) % MOD;
}

ll add (ll x, ll y) {
	return (x + y) % MOD;
}

ll binPow (ll x, ll y) {
	ll res = x;
	ll ans = 1;
	while (y > 0) {
		if (y & 1) {
			ans = mult(ans, res);
		}
		y /= 2;
		res = mult(res, res);
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

int main () {
	string s;
	cin >> s;
	vector<int> v = count_occurrence(s);
	//hashing
	vector<ll> pref = {0};
	for (int i = 0; i < s.length(); i++) {
		pref.push_back(add(mult(pref.back(), base), s[i] - 'A' + 1));
	}
	vector<pair<int,int>> vec;
	for (int len = 1; len <= s.length(); len++) {
		if (get(pref, 0, len - 1) == get(pref, s.length() - len, s.length() - 1)) {
			vec.emplace_back(len, v[len]);
		}
	}
	cout << vec.size() << '\n';
	for (auto& p: vec) {
		cout << p.first << " " << p.second << '\n';
	}
}
