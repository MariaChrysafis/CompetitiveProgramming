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
    vector<pair<int64_t,int>> left;
    vector<pair<int64_t,int>> right;
    int64_t bor = 0;
    int tot = 0;
    int length = 0;
    bool okay = true;
};
vector<int64_t> powr;
Node generate (int64_t x) {
    Node ans;
    ans.left.push_back({0, 0});
    ans.left.push_back({powr[x], 1});
    ans.right = ans.left;
    ans.tot = 1;
    ans.bor = powr[x];
    ans.length = 1;
    return ans;
}
bool contains (vector<pair<int64_t,int>> &vec, int64_t x) {
    int l = 0;
    int r = vec.size() - 1;
    while (l != r) {
        int m = (l + r + 1)/2;
        if (vec[m].first == x) {
            return true;
        }
        if (vec[m].first < x) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return (vec[l].first == x);
}
Node merge (Node x, Node y) {
    if (!x.okay) return y;
    if (!y.okay) return x;
    Node ans;
    ans.left = x.left;
    ans.right = y.right;
    for (auto& p: y.left) {
        if (!contains(ans.left, (p.first | x.bor))) {
            ans.left.emplace_back(p.first | x.bor,p.second + x.length);
        }
    }
    for (auto& p: x.right) {
        if (!contains(ans.right, (p.first | y.bor))) {
            ans.right.emplace_back(p.first | y.bor,p.second + y.length);
        }
    }
    ans.bor = x.bor | y.bor;
    ans.tot = INT_MAX;
    ans.length = x.length + y.length;
    if (x.bor == ans.bor) {
        ans.tot = min(ans.tot, x.tot);
    }
    if (y.bor == ans.bor) {
        ans.tot = min(ans.tot, y.tot);
    }
    for (auto& p: x.right) {
        int l = 0;
        int r = (int)y.left.size() - 1;
        while (l != r) {
            int m = (l + r)/2;
            if ((p.first | y.left[m].first) == ans.bor) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        if (l >= 0 && l < y.left.size() && (y.left[l].first | p.first) == ans.bor) {
            ans.tot = min(ans.tot, p.second + y.left[l].second);
        }
    }
    return ans;
}
template<class T>
class SegmentTree {
public:
 
    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
        ID.okay = false;
    }
 
    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }
 
    void build (int dum, vector<int>& arr, int tl, int tr) {
        if (tl == tr) {
            if (tl < arr.size()) val[dum] = generate(arr[tl]);
            else val[dum].okay = false;
            return;
        }
        build(2 * dum + 1, arr, tl, (tl + tr)/2);
        build(2 * dum + 2, arr, (tl + tr)/2 + 1, tr);
        val[dum] = merge(val[2 * dum + 1], val[2 * dum + 2]);
    }
 
    void build (vector<int> &arr) {
        build(0,  arr, 0, N - 1);
    }
    vector<T> val;
private:
    T ID;
    int N;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K, M;
    cin >> N >> K >> M;
    SegmentTree<Node> st(N);
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    powr = {1};
    for (int i = 0; i < 51; i++) {
        powr.push_back(powr.back() * 2);
    }
    st.build(arr);
    while (M--) {
        int t;
        cin >> t;
        if (t == 2) {
            if (st.val[0].bor == powr[K + 1] - 2) {
                cout << st.val[0].tot << '\n';
            } else {
                cout << "-1\n";
            }
        } else {
            int p, v; cin >> p >> v; p--;
            st.update(p, generate(v));
        }
    }
}
