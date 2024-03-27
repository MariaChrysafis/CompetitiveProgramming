#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <set>
#include <functional>
#include <queue>
#include <map>
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
struct Adder {
    vector<int64_t> vec;
    int pref (int x) {
        int ans = 0;
        for (int i: vec) {
            ans += (i <= x);
        }
        return ans;
    }
    int suf (int x) {
        int ans = 0;
        for (int i: vec) {
            ans += (i >= x);
        }
        return ans;
    }
    int range (int l, int r) {
        return pref(r) - pref(l - 1);
    }
    void add (int64_t x) {
        vec.push_back(x);
        sort(vec.begin(), vec.end());
    }
    void clear () {
        vec.clear();
    }
    Adder () {
        vec.clear();
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Adder adder = Adder();
    vector<Query> vec;
    for (int i = 0; i < n; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        vec.emplace_back(Query(l, r, k, i));
    }
    map<int,vector<Query>> myMap;
    /* CASE 3 */
    adder.clear();
    myMap.clear();
    for (auto& q: vec) {
        myMap[q.left].push_back(q);
    }
    for (auto& p: myMap) {
        for (auto& q: myMap[p.first]) {
            adder.add(q.right);
        }
        for (auto& q: myMap[p.first]) {
            vec[q.index].ans += adder.range(q.k + q.left, q.right - 1);
        }
    }
    /*
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (j != i) {
                bool b1 = vec[j].right <= vec[i].right - 1 && vec[j].left <= vec[i].left && vec[i].k + vec[i].left <= vec[j].right;
                if (b1) {
                    vec[i].upd();
                }
            }
        }
    }
     */
    /* CASE 1 */
    myMap.clear();
    for (auto& q: vec) {
        myMap[-q.right].push_back(q);
    }
    adder.clear();
    for (auto& p: myMap) {
        for (auto& q: myMap[p.first]) {
            adder.add(q.left);
        }
        for (auto& q: myMap[p.first]) {
            vec[q.index].ans += adder.range(q.left + 1, q.right - q.k);
        }
    }
    /* CASE 2 */
    myMap.clear();
    for (auto& q: vec) {
        myMap[q.left].push_back(q);
    }
    adder.clear();
    for (auto& p: myMap) { //increasing order of left
        for (auto& q: myMap[p.first]) {
            adder.add(q.right);
        }
        for (auto& q: myMap[p.first]) {
            vec[q.index].ans += adder.suf(q.right) - 1;
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (j != i) {
                bool b4 = vec[j].right < vec[i].right && vec[i].left <= vec[j].left && vec[j].right - vec[j].left >= vec[i].k;
                if (b4) {
                    vec[i].upd();
                }
            }
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            if (j != i) {
                bool b = vec[j].right < vec[i].right && vec[j].left == vec[i].left && vec[j].right - vec[j].left >= vec[i].k;
                if (b) {
                    vec[i].ans -= 1;
                }
            }
        }
    }
    sort(vec.begin(), vec.end(), compIndex);
    for (auto& p: vec) {
        cout << p.ans << '\n';
    }
}
