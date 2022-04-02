#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>

using namespace std;

template<class T>
class SegmentTreeMin {
public:

    SegmentTreeMin (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = INT_MAX;
    T merge (T x, T y) {
        return min(x, y);
    }
    int N;
};

template<class T>
class SegmentTreeMax {
public:

    SegmentTreeMax (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return max(x, y);
    }
    int N;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    SegmentTreeMax<int> st_max(N - 1);
    SegmentTreeMin<int> st_min(N - 1);
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < N - 1; i++) {
        if (a[i] < a[i + 1]) {
            st_min.update(i, (a[i + 1] + a[i] + 1)/2);
        }
    }
    for (int i = 0; i < N - 1; i++) {
        if (a[i] > a[i + 1]) {
            st_max.update(i, (a[i + 1] + a[i] + 1)/2);
        }
    }
    while (Q--) {
        int t; cin >> t;
        if (t == 2) {
            int x, y; cin >> x >> y; x--, y--;
            int a1 = st_max.query(x, y - 1);
            int a2 = st_min.query(x, y - 1);
            if (a1 > a2) {
                cout << "-1\n";
                continue;
            }
            cout << a1 << '\n';
        } else {
            int x, y; cin >> x >> y; x--;
            a[x] = y;
            if (a[x] < a[x + 1]) {
                st_min.update(x, (a[x + 1] + a[x] + 1)/2);
                st_max.update(x, 0);
            } else if (a[x] == a[x + 1]) {
                st_min.update(x, INT_MAX);
                st_max.update(x, 0);
            } else {
                st_max.update(x, (a[x + 1] + a[x] + 1)/2);
                st_min.update(x, INT_MAX);
            }
            if (x >= 0) {
                if (a[x - 1] < a[x]) {
                    st_min.update(x -1, (a[x - 1] + a[x] + 1)/2);
                    st_max.update(x - 1, 0);
                } else if (a[x] == a[x - 1]) {
                    st_min.update(x - 1, INT_MAX);
                    st_max.update(x - 1, 0);
                } else {
                    st_max.update(x - 1, (a[x - 1] + a[x] + 1)/2);
                    st_min.update(x - 1, INT_MAX);
                }
            }
        }
    }


}
