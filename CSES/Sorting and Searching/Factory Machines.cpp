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
vector<int64_t> v;
int64_t n, t;
int64_t amount (int64_t x) {
    int64_t ans = 0;
    for (int64_t i: v) {
        ans += x/i;
        if (ans >= t) return t;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> t;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int64_t l = 0;
    int64_t r = 1e18;
    while (l != r) {
        int64_t m = (l + r)/2;
        if (amount(m) >= t) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l;
}
