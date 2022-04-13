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

using namespace std;
class XOR_Vector_Space {
public:
    XOR_Vector_Space() {

    }
    void add_int (int64_t x) {
        for (int64_t i: basis) x = min(x, x ^ i);
        if (x != 0) basis.push_back(x);
    }
    vector<int64_t> basis;
};
int64_t solve (vector<int64_t> v) {
    int64_t X = 0;
    for (int64_t i: v) {
        X ^= i;
    }
    assert(X == 0);
    XOR_Vector_Space xvs;
    for (int64_t i: v) {
        xvs.add_int(i);
    }
    sort(xvs.basis.begin(), xvs.basis.end()), reverse(xvs.basis.begin(), xvs.basis.end());
    int64_t x = 0;
    for (int64_t i: xvs.basis) {
        x = max(x, x ^ i);
    }
    return x;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t N, X = 0; cin >> N; vector<int64_t> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i]; X ^= v[i];
    }
    XOR_Vector_Space xvs;
    for (int i = 0; i < N; i++) {
        int64_t powr = 1;
        for (int64_t j = 0; j < 64; j++) {
            if ((X & powr) && (v[i] & powr)) {
                v[i] ^= powr;

            }
            powr *= 2;
        }
    }
    cout << 2 * solve(v) + X << '\n';
}
