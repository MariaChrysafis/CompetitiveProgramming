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

    bool operator==(const Triple &t1) const {
        return (t1.x == x && t1.y == y && t1.z == z);
    }
};

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

    ll get(vector<ll> &h, vector<ll> &powr, int MOD, ll l, ll r) {
        return (h[r + 1] - mult(h[l], powr[r - l + 1], MOD) + MOD) % MOD;
    }

    bool isEqual(int l1, int r1, int l2, int r2) {
        return (get(l1, r1) == get(l2, r2));
    }

    string s;
    const int base = 29;
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
            h.push_back(mult(h.back(), base, MOD) + (s[i] - 'a' + 1));
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

struct SuffixArray {
    vector<int> a;
    string s;

    SuffixArray(const string &_s) : s(_s + '\0') {
        int N = s.size();
        vector<pair<long long, int>> b(N);
        a.resize(N);
        for (int i = 0; i < N; i++) {
            b[i].first = s[i];
            b[i].second = i;
        }

        int q = 8;
        while ((1 << q) < N) q++;
        for (int moc = 0;; moc++) {
            //count_sort(b, q); // sort(all(b)) can be used as well
            sort(b.begin(), b.end());
            a[b[0].second] = 0;
            for (int i = 1; i < N; i++)
                a[b[i].second] = a[b[i - 1].second] +
                                 (b[i - 1].first != b[i].first);

            if ((1 << moc) >= N) break;
            for (int i = 0; i < N; i++) {
                b[i].first = (ll) a[i] << q;
                if (i + (1 << moc) < N)
                    b[i].first += a[i + (1 << moc)];
                b[i].second = i;
            }
        }
        for (int i = 0; i < a.size(); i++) a[i] = b[i].second;
    }

    int lower_bound(string t) {
        int l = 1, r = a.size();
        while (l < r) {
            int m = (l + r) / 2;
            if (s.substr(a[m], min(s.size() - 1 - a[m], t.size() + 1)) >= t) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }

    int upper_bound(string t) {
        int l = 1, r = a.size();
        while (l < r) {
            int m = (l + r) / 2;
            if (s.substr(a[m], min((int) a.size() - 1 - a[m], (int) t.size())) > t) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
};

int get(vector<int> &v, int k) {
    if (v.size() < k) {
        return -1;
    }
    int myMin = INT_MAX;
    for (int i = 0; i < v.size() - k + 1; i++) {
        myMin = min(v[i + k - 1] - v[i], myMin);
    }
    return myMin;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    SuffixArray bfsa(s);
    Hasher hash(s);
    int q;
    cin >> q;
    while (q--) {
        int k;
        string str;
        cin >> k >> str;
        if (str.length() > s.length()) {
            cout << "-1\n";
            continue;
        }
        Hasher h(str);
        int l = bfsa.lower_bound(str);
        int r = bfsa.upper_bound(str);
        vector<int> vec;
        for (int i = l; i < r; i++) {
            vec.push_back(bfsa.a[i]);
        }
        sort(vec.begin(), vec.end());
        int val = get(vec, k);
        if (val == -1) {
            cout << "-1\n";
            continue;
        }
        cout << val + str.length() << '\n';
    }

}
