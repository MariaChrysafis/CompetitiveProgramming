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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

int MAXX = (int)200000 + 10;
int MAXY = (int)200000 + 10;
template<class T>
class SegmentTree {
public:

    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] += y;
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
        return x + y;
    }
    int N;
};
void compress (vector<pair<int,int>> &vec) {
    set<int> x, y;
    for (auto& p: vec) x.insert(p.first), y.insert(p.second);
    map<int,int> myMap1, myMap2;
    int cnt = 1;
    for (int x1: x) {
        myMap1[x1] = (cnt += 2);
    }
    cnt = 1;
    for (int y1: y) {
        myMap2[y1] = (cnt += 2);
    }
    for (int i = 0; i < vec.size(); i++) {
        vec[i].first = myMap1[vec[i].first];
        vec[i].second = myMap2[vec[i].second];
    }
}
int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<pair<int,int>> vec(N);
    vector<vector<int>> coord1(MAXY);
    vector<vector<int>> coord2(MAXX);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    compress(vec);
    for (int i = 0; i < N; i++) {
        //cout << vec[i].first << " " << vec[i].second << '\n';
        coord1[vec[i].second].push_back(vec[i].first);
        coord2[vec[i].first].push_back(vec[i].second);
    }
    SegmentTree<int> stL(MAXY);
    SegmentTree<int> stR(MAXY);
    for (int i = 0; i < MAXY; i++) {
        stR.update(i, coord1[i].size());
    }
    int myMin = INT_MAX;
    for (int x = 0; x < MAXX; x++) {
        if (x % 2 == 1) {
            for (int y: coord2[x]) {
                stL.update(y, 1);
                stR.update(y, -1);
            }
            continue;
        }
        for (int dum = 0; dum <= 1; dum++) {
            int l = 0;
            int r = MAXY - 2;
            int tot = stL.query(0, MAXY - 1);
            while (l != r) {
                int m = (l + r) / 2;
                if (stL.query(0, m) >= tot / 2 + dum) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            int y = l;
            int lower_left = stL.query(0, y);
            int upper_left = tot - lower_left;
            int lower_right = stR.query(0, y);
            int upper_right = stR.query(y + 1, MAXY - 1);
            assert(lower_left + upper_right + upper_left + lower_right == N);
            myMin = min(myMin, max(max(lower_right, upper_right), max(lower_left, upper_left)));
        }
    }
    cout << myMin;

}
