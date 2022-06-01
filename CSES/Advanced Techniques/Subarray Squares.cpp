#include <iostream>
#include <climits>
#include <vector>
#include <set>
#include <deque>
#include <cassert>
using namespace std;
struct convex {
    deque<int64_t> a, b;
 
    void init() {
        a.clear();
        b.clear();
    }
 
    void push(int64_t n, int64_t m, int v) {
        while (a.size() > 1 &&
               (b[b.size() - 2] - b.back()) * (n - a.back()) >= (b.back() - m) * (a.back() - a[a.size() - 2])) {
            a.pop_back();
            b.pop_back();
        }
        a.push_back(n);
        b.push_back(m);
    }
 
    int64_t query(int64_t x) {
        while (a.size() > 1 && (a[1] - a[0]) * x > (b[0] - b[1])) {
            a.pop_front();
            b.pop_front();
        }
        return a[0] * x + b[0];
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int64_t pref[n + 1];
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        int64_t x; cin >> x;
        pref[i] = pref[i - 1] + x;
    }
    vector<int64_t> prev, cur;
    prev.assign(n + 1, LLONG_MAX);
    cur.assign(n + 1, LLONG_MAX);
    for (int i = 0; i <= n; i++) {
        cur[i] = pref[i] * pref[i];
    }
    for (int j = 2; j <= k; j++) {
        swap(prev, cur);
        cur.assign(n + 1, LLONG_MAX);
        cur[0] = 0;
        convex lc;
        for (int i = 1; i <= n; i++) {
            lc.push(2 * pref[i - 1], -prev[i - 1] - pref[i - 1] * pref[i - 1], 0);
            cur[i] = pref[i] * pref[i] - lc.query(pref[i]);
        }
    }
    cout << cur[n];
}
