#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>
#include <iomanip>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
typedef long long ll;
vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};
vector<int> prime;
vector<ll> powr = {1};
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
struct Node {
    ll mask = 0;
    ll prod = 1;
};

Node merge (Node a, Node b) {
    Node ans;
    ans.prod = mult(a.prod, b.prod);
    ans.mask = (a.mask | b.mask);
    return ans;
}
Node generate (int x) {
    Node ans;
    for (int i = 0; i < primes.size(); i++) {
        if (x % primes[i] == 0) {
            ans.mask += powr[i];
        }
    }
    ans.prod = x;
    return ans;
}

Node Pow (Node x, int y) {
    Node res = x;
    Node ans;
    while (y > 0) {
        if (y & 1) {
            ans = merge(res, ans);
        }
        res = merge(res, res);
        y /= 2;
    }
    return ans;
}

Node emp;

struct segmentTree {
    vector<Node> vec;
    vector<Node> addLater;

    void push(int v, int tl, int tr) {
        int tm = (tl + tr)/2;
        addLater[2 * v + 1] = merge(addLater[v], addLater[2 * v + 1]);
        vec[2 * v + 1] = merge(Pow(addLater[v], tr - tm), vec[2 * v + 1]);
        addLater[2 * v] = merge(addLater[v], addLater[2 * v]);
        vec[2 * v] = merge(Pow(addLater[v], tm - tl + 1), vec[2 * v]);
        addLater[v] = emp;
    }


    void upd(int dum, int tl, int tr, int l, int r, Node val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] = merge(val, addLater[dum]);
            vec[dum] = merge(vec[dum], Pow(val, tr - tl + 1));
            return;
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = merge(vec[2 * dum], vec[2 * dum + 1]);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, generate(val));
    }

    Node get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return emp;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return merge(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    Node get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    prime.resize(primes.size());
    for (int i = 0; i < primes.size(); i++) {
        prime[i] = inv(primes[i] - 1);
    }
    while (powr.size() <= primes.size()) {
        powr.push_back(powr.back() * 2);
    }
    int N, Q;
    cin >> N >> Q;
    segmentTree st;
    st.resz(N);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        st.upd(i, i, x);
    }
    while (Q--) {
        string s;
        cin >> s;
        if (s == "TOTIENT") {
            int l, r;
            cin >> l >> r;
            l--, r--;
            Node res = st.get(l, r);
            ll pr = res.prod;
            ll msk = res.mask;
            for (int i = 0; i < primes.size(); i++) {
                if (msk & powr[i]) {
                    pr = mult(pr, primes[i] - 1);
                    pr = mult(pr, inv(primes[i]));
                }
            }
            cout << pr << '\n';
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            st.upd(l, r, x);
        }
    }
}
