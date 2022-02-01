#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
typedef int64_t ll;
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 1e9;

    ll op(ll a, ll b) {
        return min(a,b);
    }

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = op(op(query(curX, x - 1), query(x + 1, curY)), y);
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }

};
int l = 0;
int r = -1;
int sq = -1;
int ans = 0;
vector<set<int>> oc;
vector<int> arr;
segmentTree st;
bool comp (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    assert(sq != -1);
    return ((pair<int,int>){p1.first.first/sq, p1.first.second} < (pair<int,int>){p2.first.first/sq, p2.first.second});
}
int prevOc (set<int>& s, int ind) {
//    cout << "INDEX " << ind << '\n';
    assert(s.find(ind) != s.end());
    auto it = s.lower_bound(ind);
    if (it == s.begin()) return -1;
    it--;
    return *it;
}
int nxtOc (set<int>& s, int ind) {
//    assert(s.find(ind) != s.end());
    auto it = s.upper_bound(ind);
    if (it == s.end()) return -1;
    return *it;
}
void addRight (int ind) {
//    cout << "ADD RIGHT " << l << " " << r << '\n';
    assert(ind == r + 1);
    r++;
    if (prevOc(oc[arr[ind]], ind) < l) {
        ans++;
        return;
    }
    int i = prevOc(oc[arr[ind]], ind);
    if (st.query(i, ind) == arr[i]) {
        return;
    }
    ans++;
}
void removeRight (int ind) {
//    cout << "REMOVE RIGHT " << l << " " << r << '\n';
    assert(ind == r);
    r--;
    if (prevOc(oc[arr[ind]], ind) < l) {
        ans--;
        return;
    }
    int i = prevOc(oc[arr[ind]], ind);
    if (st.query(i, ind) == arr[i]) {
        return;
    }
    ans--;
}
void removeLeft (int ind) {
//    cout << "REMOVE LEFT " << l << " " << r << '\n';
    assert(ind == l);
    l++;
    if (nxtOc(oc[arr[ind]], ind) > r) {
        ans--;
        return;
    }
    int i = nxtOc(oc[arr[ind]], ind);
    if (st.query(ind, i) == arr[i]) {
        return;
    }
    ans--;
}
void addLeft (int ind) {
//    cout << "ADD LEFT " << l << " " << r << '\n';
    assert(ind == l - 1);
    l--;
    if (nxtOc(oc[arr[ind]], ind) > r) {
        ans++;
        return;
    }
    int i = nxtOc(oc[arr[ind]], ind);
    if (st.query(ind, i) == arr[i]) {
        return;
    }
    ans++;
}
int main() {
    int N, Q;
    cin >> N >> Q;
    st.resz(N);
    oc.resize(N), arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i]; arr[i]--;
        oc[arr[i]].insert(i);
        st.update(i, arr[i]);
    }
    sq = sqrt(N);
    vector<pair<pair<int,int>,int>> vec(Q);
    for (int i = 0; i < Q; i++) {
        cin >> vec[i].first.first >> vec[i].first.second;
        vec[i].first.first--, vec[i].first.second--;
        vec[i].second = i;
    }
    sort(vec.begin(), vec.end(), comp);
    vector<int> res;
    res.resize(Q);
    for (auto& pr: vec) {
        pair<int,int> p = pr.first;
//        cout << "PAIR " << p.first << " " << p.second << '\n';
        while (r < p.second) {
            addRight(r + 1);
        }
        while (r > p.second) {
            removeRight(r);
        }
        while (l < p.first) {
            removeLeft(l);
        }
        while (l > p.first) {
            addLeft(l - 1);
        }
        //cout << ans << '\n';
        res[pr.second] = ans;
    }
    for (int i: res) {
        cout << i << '\n';
    }
}
