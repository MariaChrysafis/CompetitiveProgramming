#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    signed long long ans[2];
    ans[0] = ans[1] = 0;
    for (int i = 1; i < (1 << k); i++) {
        signed long long mult = 1;
        double lg2 = 0;
        for (int j = 0; j < k ;j++) {
            if ((1 << j) & i) {
                lg2 += log2(a[j]);
            }
        }
        if (lg2 > log2(n)) {
            continue;
        }
        for (int j = 0; j < k; j++) {
            if ((1 << j) & i) {
                mult *= a[j];
            }
        }
        ans[__builtin_popcount(i) % 2] += n/mult;
    }
    cout << ans[1] - ans[0];
}
