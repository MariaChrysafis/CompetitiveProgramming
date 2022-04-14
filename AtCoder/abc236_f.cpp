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
typedef long long ll;

using namespace std;
class XorBasis {
public:
    vector<int64_t> bases;
    bool add (int64_t x) {
        for (int i: bases) {
            x = min(x, x ^ i);
        }
        if (x == 0) {
            return false;
        }
        bases.push_back(x);
        return true;
    }
    XorBasis() {

    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int64_t,int64_t>> vec((1 << n) - 1);
    for (int i = 0; i < (1 << n) - 1; i++) {
        cin >> vec[i].first;
        vec[i].second = i + 1;
    }
    sort(vec.begin(), vec.end());
    XorBasis xb;
    int64_t ans = 0;
    for (int i = 0; i < vec.size(); i++) {
        ans += xb.add(vec[i].second) * vec[i].first;
    }
    cout << ans;
}
