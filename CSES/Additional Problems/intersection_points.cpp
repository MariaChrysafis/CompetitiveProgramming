#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <bitset>
#include <string>
#include <queue>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
#define ll long long
 
#include <map>
 
 
using namespace std;
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
        return x + y;
    }
    int N;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<pair<pair<int,int>, pair<int,int>>> vec(N);
    set<int> s;
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first.first >> vec[i].first.second >> vec[i].second.first >> vec[i].second.second;
        s.insert(vec[i].first.first), s.insert(vec[i].first.second), s.insert(vec[i].second.first), s.insert(vec[i].second.second);
    }
    map<int,int> myMap;
    int cntr = 0;
    for (int i: s) {
        myMap[i] = cntr++;
    }
    vector<vector<pair<int,int>>> h(4 * N + 2);
    vector<vector<pair<int,int>>> v(4 * N + 2);
    SegmentTree<int> st(4 * N + 2);
    for (int i = 0; i < vec.size(); i++) {
        vec[i].first.first = myMap[vec[i].first.first];
        vec[i].first.second = myMap[vec[i].first.second];
        vec[i].second.first = myMap[vec[i].second.first];
        vec[i].second.second = myMap[vec[i].second.second];
        //cout << vec[i].first.first << " " << vec[i].first.second << " " << vec[i].second.first << " " << vec[i].second.second << '\n';
        if (vec[i].first.second == vec[i].second.second) {
            h[vec[i].first.first].push_back({1, vec[i].first.second});
            h[vec[i].second.first].push_back({-1, vec[i].second.second});
        } else {
            v[vec[i].first.first].emplace_back(vec[i].first.second, vec[i].second.second);
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < h.size(); i++) {
        for (pair<int,int> p: h[i]) {
            //cout << "UDPATE " << p.second << '\n';
            if (p.first == 1) {
                st.update(p.second, 1);
            } else {
                st.update(p.second, 0);
            }
        }
        for (pair<int,int> p: v[i]) {
            //cout << "QUERY " << p.first << " " << p.second << '\n';
            ans += st.query(p.first, p.second);
        }
    }
    cout << ans;
 
}
