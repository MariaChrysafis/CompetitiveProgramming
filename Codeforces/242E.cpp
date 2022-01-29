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
struct SegmentTree {
    vector<ll> vec;
    vector<bool> setLater;

    void push(int v, int tl, int tr) {
        if (setLater[v] == false) {
            return;
        }
        int tm = (tl + tr)/2;
        setLater[2 * v + 1] = !setLater[2 * v + 1];
        setLater[2 * v] = !setLater[2 * v];
        vec[2 * v + 1] = (tr - tm) - vec[2 * v + 1];
        vec[2 * v] = (tm - tl + 1) - vec[2 * v];
        setLater[v] = false;
    }

    const ll INF = 0;

    ll upd(int dum, int tl, int tr, int l, int r) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            setLater[dum] = !setLater[dum];
            return (vec[dum] = (tr - tl + 1) - vec[dum]);
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r);
        upd(2 * dum + 1, mid + 1, tr, l, r);
        return (vec[dum] = vec[2 * dum] + vec[2 * dum + 1]);
    }

    void upd(int l, int r) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    ll get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return get(dum * 2, tl, tm, l, r) + get(dum * 2 + 1, tm + 1, tr, l, r);
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, 0);
        setLater.assign(sz * 2, false);
    }
};
const int BITS = 21;
SegmentTree segmentTree[BITS];
void upd (int l, int r, int x) {
	//range XOR l...r with x
	for (int i = 0; i < BITS; i++) {
		if (x & (1 << i)) {
			segmentTree[i].upd(l, r); //range flip from l...r
		}
	}
}
ll sum (int l, int r) {
	ll powr = 1;
	ll ans = 0;
	for (int i = 0; i < BITS; i++) {
		ans += powr * segmentTree[i].get(l, r);
		powr *= 2;
	}
	return ans;
}
int main () {
	int N;
	cin >> N;
	for (int i = 0; i < BITS; i++) {
		segmentTree[i].resz(N);
	}
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		upd(i, i, x);
	}
	int Q;
	cin >> Q;
	while (Q--) {
		int t;
		cin >> t;
		int l, r; 
		cin >> l >> r;
		l--, r--;
		if (t == 1) {
			cout << sum(l, r) << '\n';
		} else {
			int x; cin >> x;
			upd(l, r, x);
		}
	}
}
