#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
 
using namespace std;
 
struct lex_compare {
    bool operator()(pair<int, int> p, pair<int, int> q) const {
        return make_pair(p.second - p.first, p.first) < make_pair(q.second - q.first, q.first);
    }
};
 
set<pair<int, int>> intervals;
multiset<int> cst;
vector<bool> s;
 
void insert_interval(pair<int, int> p) {
    intervals.insert(p), cst.insert(p.second - p.first);
}
 
void merge(pair<int, int> &p1, pair<int, int> &p2) {
    intervals.erase(p1), cst.erase(cst.lower_bound(p1.second - p1.first));
    intervals.erase(p2), cst.erase(cst.lower_bound(p2.second - p2.first));
    intervals.insert({p1.first, p2.second}), cst.insert(p2.second - p1.first);
}
 
void update(int x) {
    s[x] = !s[x];
    pair<int, int> p = (*(--intervals.upper_bound({x + 1, -1})));
    if (s[p.second] != s[x] || s[p.first] != s[x]) {
        intervals.erase(p), cst.erase(cst.lower_bound(p.second - p.first));
        if (p.first <= x - 1) insert_interval({p.first, x - 1});
        intervals.insert({x, x}), cst.insert(0);
        if (x + 1 <= p.second) insert_interval({x + 1, p.second});
        p = {x, x};
    }
    if (x >= 1 && s[x] == s[x - 1]) {
        pair<int, int> pr = *(prev(intervals.upper_bound({x, -1})));
        if (p != pr) {
            merge(pr, p);
            p = {pr.first, p.second};
        }
    }
    if (x + 1 != s.size() && s[x] == s[x + 1]) {
        pair<int, int> pr = *(prev(intervals.upper_bound({x + 2, 0})));
        if (p != pr) {
            merge(p, pr);
        }
    }
}
 
void init(vector<bool> &v) {
    s = v;
    intervals.insert({0, s.size() - 1});
    cst.insert(s.size() - 1);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string str;
    cin >> str;
    int Q;
    cin >> Q;
    vector<bool> v;
    v.assign(str.length(), false);
    init(v);
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '1') {
            update(i);
        }
    }
    auto it = cst.begin();
    int x;
    while (Q--) {
        cin >> x;
        update(x - 1);
        it = cst.end();
        cout << (*(--it)) + 1 << ' ';
    }
}
