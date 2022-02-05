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

ll mult(ll x, ll y, int MOD) {
    x %= MOD, y %= MOD;
    return (x * y) % MOD;
}

struct Triple {
    int x, y, z;

    bool operator<(const Triple &t1) const {
        pair<pair<int, int>, int> p = {{t1.x, t1.y}, t1.z};
        pair<pair<int, int>, int> q = {{x, y}, z};
        return (p < q);
    }
};

string addBinary(string A) {
    for (int i = A.length() - 1; i >= 0; i--) {
        if (A[i] == '0') {
            A[i] = '1';
            break;
        } else {
            A[i] = '0';
        }
    }
    return A;
}

class Hasher {
public:
    Hasher(string str) {
        this->s = str;
        init_hash(h1, MOD1);
        init_hash(h2, MOD2);
        init_hash(h3, MOD3);
        init_powr();
    }

    Triple get(ll l, ll r) {
        ll x1 = (h1[r + 1] - mult(h1[l], powr1[r - l + 1], MOD1) + MOD1) % MOD1;
        ll x2 = (h2[r + 1] - mult(h2[l], powr2[r - l + 1], MOD2) + MOD2) % MOD2;
        ll x3 = (h3[r + 1] - mult(h3[l], powr3[r - l + 1], MOD3) + MOD3) % MOD3;
        return (Triple) {(int) x1, (int) x2, (int) x3};
    }

    string s;
    const int base = 2;
    vector<ll> h1;
    const int MOD1 = 1000000223;
    vector<ll> h2;
    const int MOD2 = 1e9 + 9;
    vector<ll> h3;
    const int MOD3 = 998244353;
    vector<ll> powr1, powr2, powr3;

    void init_hash(vector<ll> &h, int MOD) {
        h.push_back(0);
        for (int i = 0; i < s.size(); i++) {
            h.push_back(mult(h.back(), base, MOD) + (s[i] - '0'));
            h.back() %= MOD;
        }
    }

    void init_powr() {
        powr1 = powr2 = powr3 = {1};
        while (powr1.size() != h1.size() + 1) {
            powr1.push_back(mult(powr1.back(), base, MOD1));
            powr2.push_back(mult(powr2.back(), base, MOD2));
            powr3.push_back(mult(powr3.back(), base, MOD3));
        }
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '0') {
            s[i] = '1';
        } else {
            s[i] = '0';
        }
    }
    Hasher hash(s);
    map<Triple, int> myMap;
    for (int i = 0; i <= s.length() - k; i++) {
        myMap[hash.get(i, i + k - 1)]++;
        //cout << hash.get(i, i + k - 1).x << " " << hash.get(i, i + k - 1).y << " " << hash.get(i, i + k - 1).z << '\n';
    }
    for (int i = 0; i >= 0; i++) {
        if (log2(i) >= k) {
            break;
        }
        if (!myMap[{i, i, i}]) {
            cout << "YES\n";
            for (int j = k - 1; j >= 0; j--) {
                if (j <= 30 && (i & (1 << j))) cout << 1;
                else cout << 0;
            }
            cout << '\n';
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
