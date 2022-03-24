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
    int64_t left;
    int64_t right;
    int64_t tot;
    bool is_full = true;
    Node (int x) {
        if (x == 0) {
            left = right = tot = 0;
            is_full = false;
        } else {
            left = right = tot = 1;
        }
    }
};
 
int64_t c2 (int64_t x) {
    return (x * (x + 1))/2;
}
 
Node merge (Node x, Node y) {
    Node ans(-1);
    ans.tot = x.tot + y.tot - c2(x.right) - c2(y.left) + c2(x.right + y.left);
    ans.left = x.left;
    ans.right = y.right;
    if (x.is_full) {
        ans.left += y.left;
    }
    if (y.is_full) {
        ans.right += x.right;
    }
    ans.is_full = (x.is_full && y.is_full);
    return ans;
}
 
class SegmentTree {
public:
 
    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, Node(0));
    }
 
    void update (int x, Node y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }
    vector<Node> val;
private:
    int N;
};
 
int64_t rectangle_count (vector<int64_t> histogram) {
    SegmentTree st(histogram.size());
    vector<vector<int64_t>> height;
    for (int i = 0; i < histogram.size(); i++) {
        st.update(i, Node(1));
        while (histogram[i] >= height.size()) {
            height.emplace_back();
        }
        height[histogram[i]].push_back(i);
    }
    vector<int> v;
    v.assign(histogram.size(), 1);
    int64_t ans = 0;
    for (int i = 0; i < height.size(); i++) {
        for (int64_t j: height[i]) {
            st.update(j, Node(0));
            v[j] = 0;
        }
        ans += st.val[0].tot;
        //ans += st.val[0].tot;
    }
    return ans;
}
int main() {
//    freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> arr(N);
    for (int i = 0; i < N; i++) {
        arr[i].resize(M);
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }
    vector<int64_t> his;
    his.assign(M, 1);
    int64_t ans = 0;
    for (int r = N - 1; r >= 0; r--) {
        for (int c = 0; c < M; c++) {
            his[c]--;
        }
        for (int c = 0; c < M; c++) {
            if (his[c] == 0) {
                int t = r;
                int cnt = 0;
                while (t >= 0 && arr[r][c] == arr[t][c]) {
                    t--;
                    cnt++;
                }
                his[c] = cnt;
            }
        }
        vector<vector<int64_t>> h;
        for (int c = 0; c < M; c++) {
            if (c == 0 || arr[r][c] != arr[r][c - 1]) {
                h.push_back({his[c]});
            } else {
                h.back().push_back(his[c]);
            }
        }
        for (auto& vec: h) {
            ans += rectangle_count(vec);
        }
    }
    cout << ans;
}
