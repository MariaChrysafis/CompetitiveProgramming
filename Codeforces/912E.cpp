#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
class Tester {
public:
    vector<int64_t> p;
    vector<int64_t> tot;
    void res (int ind, int64_t K, int64_t a) {
        if (K == 0) return;
        if (ind == -1) {
            tot.push_back(a);
            return;
        }
        while (K > 0) {
            res(ind - 1, K, a);
            K /= p[ind];
            a *= p[ind];
        }
    }
    vector<int64_t> test (int64_t m) {
        tot.clear();
        res ((int)p.size() - 1, m, 1);
        return tot;
    }
};
int64_t K;
int64_t merge (vector<int64_t> &v1, vector<int64_t> &v2, int64_t k) {
    int l = 0;
    int r = v2.size() - 1;
    int64_t ans = 0;
    while (l < v1.size() && r >= 0) {
        bool d = false;
        while (r >= 0 && v1[l] >= (k + v2[r] - 1)/v2[r]) {
            r--;
            d = true;
        }
        if (d) continue;
        ans += r + 1;
        l++;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; cin >> N;
    deque<int64_t> p(N); for (int i = 0; i < N; i++) cin >> p[i];
    Tester t1, t2;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) t1.p.push_back(p[i]);
        else t2.p.push_back(p[i]);
    }
    reverse(t1.p.begin(), t1.p.end());
    reverse(t2.p.begin(), t2.p.end());
    cin >> K;
    int64_t l = 0;
    int64_t r = LLONG_MAX;
    vector<int64_t> v1 = t1.test(LLONG_MAX);
    vector<int64_t> v2 = t2.test(LLONG_MAX);
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    while (l != r) {
        int64_t m = (l + r)/2;
        if (merge(v1, v2, m) >= K) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l - 1 << '\n';
}
