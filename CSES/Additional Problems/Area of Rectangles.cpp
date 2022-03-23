#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>
 
using namespace std;
 
class Node {
public:
    int64_t mn = 0;
    int64_t cnt = 1;
    bool okay = true;
};
 
Node merge (Node x, Node y) {
    if (!x.okay) return y;
    if (!y.okay) return x;
    Node ans;
    if (x.mn == y.mn) {
        ans.mn = x.mn;
        ans.cnt = x.cnt + y.cnt;
    } else if (x.mn < y.mn){
        ans = x;
    } else if (y.mn < x.mn) {
        ans = y;
    }
    return ans;
}
 
void update(Node &x, int64_t val) {
    x.mn += val;
}
 
Node INF;
 
struct segmentTree {
    vector<Node> vec;
    vector<int64_t> addLater;
 
    void push(int v) {
        addLater[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        vec[2 * v + 1].mn += addLater[v];
        vec[2 * v].mn += addLater[v];
        addLater[v] = 0;
    }
 
    void upd(int dum, int tl, int tr, int l, int r, int64_t val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            update(vec[dum], val);
            return;
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = merge(vec[2 * dum], vec[2 * dum + 1]);
    }
 
    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }
 
    void init (int dum, int tl, int tr) {
        if (tl == tr) {
            vec[dum].mn = 0;
            vec[dum].cnt = 1;
            return;
        }
        int mid = (tl + tr) >> 1;
        init(2 * dum, tl, mid);
        init(2 * dum + 1, mid + 1, tr);
        vec[dum] = merge(vec[2 * dum], vec[2 * dum + 1]);
    }
 
    Node get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            //cout << tl << " " << tr <<  " " << vec[dum].cnt << '\n';
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return merge(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }
 
    Node get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }
 
    vector<int> arr;
 
    void resz(int n) {
        //INF.okay = false;
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, INF);
        addLater.resize(sz * 2);
        arr.resize(sz);
        INF.okay = false;
        init(1, 0, (int)vec.size()/2 - 1);
    }
 
};
const int MAX = 1e6 + 10;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    segmentTree st;
    st.resz(2 * MAX);
    int N;
    cin >> N;
    vector<pair<int64_t,pair<pair<int64_t,int64_t>,int64_t>>> events;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        y1++;
        x1 += MAX, y1 += MAX, x2 += MAX, y2 += MAX;
        events.push_back({x1, {{y1, y2}, 1}});
        events.push_back({x2, {{y1, y2}, -1}});
    }
    int64_t ans = 0;
    sort(events.begin(), events.end());
    st.upd(events[0].second.first.first, events[0].second.first.second, 1);
    for (int i = 1; i < 2 * N; i++) {
        int64_t qr = 2 * MAX - st.get(0, 2 * MAX - 1).cnt;
        ans += qr * (events[i].first - events[i - 1].first);
        st.upd(events[i].second.first.first, events[i].second.first.second, events[i].second.second);
    }
    cout << ans;
 
}
