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
#include <queue>
#include <limits.h>
 
using namespace std;
 
struct convex {
    deque<int64_t> a, b;
    deque<int> c;
 
    void init() {
        a.clear();
        b.clear();
        c.clear();
    }
 
    void push(int64_t n, int64_t m, int v) {
        while (a.size() > 1 &&
               (b[b.size() - 2] - b.back()) * (n - a.back()) >= (b.back() - m) * (a.back() - a[a.size() - 2])) {
            a.pop_back();
            b.pop_back();
            c.pop_back();
        }
        a.push_back(n);
        b.push_back(m);
        c.push_back(v);
    }
 
    pair<int64_t, int> query(int64_t x) {
        while (a.size() > 1 && (a[1] - a[0]) * x > (b[0] - b[1])) {
            a.pop_front();
            b.pop_front();
            c.pop_front();
        }
        return make_pair(a[0] * x + b[0], c[0]);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int64_t arr[n];
    int64_t pref[n + 1];
    pref[0] = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        pref[i + 1] = pref[i] + arr[i];
    }
    vector<int64_t> dp_cur(n - 1), dp_prev(n - 1);
    int prev[n - 1][k + 1];
    for (int i = 0; i < n - 1; i++) {
        dp_prev[i] = (pref[i + 1]) * (pref[n] - pref[i + 1]);
        prev[i][1] = -1;
    }
    for (int j = 2; j <= k; j++) {
        convex cht;
        dp_cur[0] = 0;
        for (int i = 1; i < n - 1; i++) {
            cht.push(pref[i], dp_prev[i - 1], i);
            auto p = cht.query(pref[i + 1] - pref[n]);
            dp_cur[i] = p.first + pref[i + 1] * pref[n] - pref[i + 1] * pref[i + 1];
            prev[i][j] = p.second - 1;
        }
        dp_prev = dp_cur;
    }
    int64_t myMax = 0;
    for (int i = 0; i < n - 1; i++) {
        myMax = max(myMax, dp_prev[i]);
    }
    cout << myMax << '\n';
    for (int i = 0; i < n - 1; i++) {
        if (myMax == dp_prev[i]) {
            int mid = i;
            int cntr = 0;
            while (cntr != k) {
                cout << mid + 1 << ' ';
                mid = prev[mid][k - cntr];
                cntr++;
            }
            return 0;
        }
    }
}
