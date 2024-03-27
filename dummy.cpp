#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <set>
#include <functional>
#include <queue>
using namespace std;
struct Query {
    int left, right, k, index, ans;
    void upd () {
        this->ans += 1;
    }
    Query (int left, int right, int k, int index) : left(left), right(right), k(k), index(index), ans(0) {

    }
};
bool compIndex (Query q1, Query q2) {
    return (q1.index < q2.index);
}
bool compK (Query q1, Query q2) {
    if (q1.k != q2.k) {
        return (q1.k < q2.k);
    }
    return (q1.index < q2.index);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<Query> vec;
    for (int i = 0; i < n; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        vec.emplace_back(Query(l, r, k, i));
    }
    sort(vec.begin(), vec.end(), compK);
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (j != i) {
                bool b1 = vec[j].left <= vec[i].left && vec[i].k + vec[i].left <= vec[j].right && vec[j].right < vec[i].right;
                bool b2 = vec[i].left <= vec[j].left && vec[i].right <= vec[j].right && vec[i].right - vec[i].k >= vec[j].left;
                bool b3 = vec[j].left <= vec[i].left && vec[i].right <= vec[j].right;
                bool b4 = vec[i].left <= vec[j].left && vec[j].right - vec[j].left >= vec[i].k && vec[j].right < vec[i].right;
                assert(!(b1 && b2));
                assert(!(b3 && b4));
                if (b1 || b2 || b3 || b4) {
                    vec[i].upd();
                }
            }
        }
    }
    sort(vec.begin(), vec.end(), compIndex);
    for (auto& p: vec) {
        cout << p.ans << '\n';
    }
}
