#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

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
    bool operator == (const Triple& t1) const {
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

    Triple get (ll l, ll r) {
        ll x1 = (h1[r + 1] - mult(h1[l], powr1[r - l + 1], MOD1) + MOD1) % MOD1;
        ll x2 = (h2[r + 1] - mult(h2[l], powr2[r - l + 1], MOD2) + MOD2) % MOD2;
        ll x3 = (h3[r + 1] - mult(h3[l], powr3[r - l + 1], MOD3) + MOD3) % MOD3;
        return (Triple) {(int) x1, (int) x2, (int) x3};
    }

    ll get (vector<ll>& h, vector<ll>& powr, int MOD, ll l, ll r) {
        return (h[r + 1] - mult(h[l], powr[r - l + 1], MOD) + MOD) % MOD;
    }
    bool isEqual (int l1, int r1, int l2, int r2) {
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

class BuildSuffixArray {
public:
    vector<int> sort_cyclic_shifts(string const& s) {
        int n = s.size();
        const int alphabet = 256;
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i - 1]])
                classes++;
            c[p[i]] = classes - 1;
        }
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        return p;
    }
    vector<int> suffix_array_construction(string s) {
        s += "$";
        vector<int> sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }

};

int longestCommonPrefix (Hasher& hash, int i1, int i2) {
    if (!hash.isEqual(i1, i1, i2, i2)) {
        return 0;
    }
    int l = 1;
    int r = hash.s.size();
    while (l != r) {
        int mid = (l + r + 1)/2;
        if (i1 + mid - 1 >= hash.s.size() || i2 + mid - 1 >= hash.s.size()) {
            r = mid - 1;
            continue;
        }
        if (hash.isEqual(i1, i1 + mid - 1, i2, i2 + mid - 1)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

void remove (set<pair<int,int>>& s, int x) {
    auto it = s.upper_bound({x + 1, -1});
    if (it == s.begin()) {
        return;
    }
    it--;
    pair<int,int> p = *it;
    if (p.first > x || p.second < x) {
        return;
    }
    s.erase(p);
    if (p.first <= x - 1) {
        s.insert({p.first, x - 1});
    }
    if (x + 1 <= p.second) {
        s.insert({x + 1, p.second});
    }
}

void update (set<pair<int,int>> &s, int x) {
    auto it = s.lower_bound({x + 1, -1});
    if (it == s.begin()) {
        return;
    }
    it--;
    pair<int,int> p = *it;
    if (x < p.first || x > p.second) {
        return;
    }
    s.erase(p);
    if (p.first <= x - 1) {
        s.insert({p.first, x - 1});
    }
    if (x <= p.second) {
        s.insert({x, p.second});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    map<Triple,int> pref;
    map<Triple,int> tot;
    while (q--) {
        int t;
        cin >> t;
        string s;
        cin >> s;
        Hasher hash(s);
        if (t == 1) {
            for (int i = 0; i < s.length(); i++) {
                pref[hash.get(0, i)]++;
            }
            tot[hash.get(0, s.length() - 1)]++;
        } else if (t == 2) {
            for (int i = 0; i < s.length(); i++) {
                pref[hash.get(0, i)]--;
            }
            tot[hash.get(0, s.length() - 1)]--;
        } else {
            BuildSuffixArray bsfa;
            vector<int> v = bsfa.suffix_array_construction(s);
            vector<vector<int>> ind(s.length() + 1);
            map<int,int> myMap;
            for (int i = 0; i < v.size(); i++) {
                myMap[v[i]] = i;
            }
            for (int i = 1; i < v.size(); i++) {
                ind[longestCommonPrefix(hash, v[i], v[i - 1])].push_back(i);
            }
            set<pair<int,int>> blocks;
            blocks.insert({0, s.length() - 1});
            int ans = 0;
            for (int j = 0; j < v.size(); j++) {
                vector<int> vec = ind[j];
                for (int i: vec) {
                    update(blocks, i);
                }
                set<pair<int,int>> to_erase;
                for (auto& p: blocks) {
                    Triple ha = hash.get(v[p.first], v[p.first] + j);
                    if (!pref[ha]) {
                        to_erase.insert(p);
                    } else {
                        ans += (p.second - p.first + 1) * tot[ha];
                    }
                }
                for (auto& p: to_erase) {
                    blocks.erase(p);
                }
                remove(blocks, myMap[v.size() - j - 1]);
            }
            cout << ans << '\n';
            cout.flush();
        }
    }
}
