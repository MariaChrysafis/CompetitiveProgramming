#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

string S;
ll K;

vector<ll> indices;
vector<ll> pref;

ll add (ll l, ll r) {
    return pref[r + 1] - pref[l];
}

ll sum (int l, int r, int ind) {
    assert(ind >= l && ind <= r);
    ll x = -add(l, ind) + indices[ind] * (ind - l + 1) + add(ind + 1, r) - indices[ind] * (r - ind);
    return x;
}

bool valid (ll len) {
    if (len == 0) {
        return true;
    }
    for (int i = 0; i <= indices.size() - len; i++) {
        if (sum(i, i + len - 1, (2 * i + len - 1)/2) <= K) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> S >> K;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == 'Y') {
            indices.push_back(i - indices.size());
        }
    }
    pref.push_back(0);
    for (int i = 0; i < indices.size(); i++) {
        pref.push_back(pref.back() + indices[i]);
    }
    int l = 0;
    int r = indices.size();
    while (l != r) {
        int m = (l + r + 1) >> 1;
        if (valid(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l;
}
