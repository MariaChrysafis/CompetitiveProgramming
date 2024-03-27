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
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (j != i) {
                if (vec[j].left <= vec[i].left && vec[i].left <= vec[j].right && vec[j].right <= vec[i].right && vec[j].right - vec[i].left >= vec[i].k) {
                    vec[i].upd();
                } else if (vec[i].left <= vec[j].left && vec[j].left <= vec[i].right && vec[i].right <= vec[j].right && vec[i].right - vec[j].left >= vec[i].k) {
                    vec[i].upd();
                } else if (vec[j].right - vec[j].left >= vec[i].k && vec[i].left <= vec[j].left && vec[j].right <= vec[i].right) {
                    vec[i].upd();
                } else if (vec[i].right - vec[i].left >= vec[i].k && vec[j].left <= vec[i].left && vec[i].right <= vec[j].right) {
                    vec[i].upd();
                }
            }
        }
    }
    for (auto& p: vec) {
        cout << p.ans << '\n';
    }
}
