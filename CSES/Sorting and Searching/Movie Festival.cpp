#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
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
        return max(x, y);
    }
    int N;
};
vector<int> dp;
void compress (vector<pair<int,int>> &vec) {
    set<int> s;
    for (auto& p: vec) s.insert(p.first), s.insert(p.second);
    map<int,int> myMap;
    int cntr = 1;
    dp.assign(s.size() + 1, 0);
    for (int i: s) myMap[i] = cntr++;
    for (auto& p: vec) p.first = myMap[p.first], p.second = myMap[p.second];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<pair<int,int>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    compress(vec);
    sort(vec.begin(), vec.end());
 
    SegmentTree<int> st(dp.size() + 1);
    for (int i = 0; i < vec.size(); i++) {
        dp[vec[i].second] = max(dp[vec[i].second], st.query(0, vec[i].first) + 1);
        st.update(vec[i].second, dp[vec[i].second]);
    }
    int myMax = 0;
    for (int i = 0; i < dp.size(); i++) {
        myMax = max(myMax, dp[i]);
    }
    cout << myMax;
}
