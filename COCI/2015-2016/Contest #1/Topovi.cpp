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
#include <limits.h>
#include <queue>
 
using namespace std;
class DynamicThing {
    map<int64_t,int64_t> oc1;
    map<int64_t,int64_t> oc2;
public:
    int64_t tot = 0;
    void remove (int64_t type, int64_t index) {
        if (type == 1) {
            tot -= oc1[index] * oc2[index];
            oc1[index]--;
            tot += oc1[index] * oc2[index];
        } else {
            tot -= oc1[index] * oc2[index];
            oc2[index]--;
            tot += oc1[index] * oc2[index];
        }
    }
    void add (int64_t type, int64_t index) {
        if (type == 1) {
            tot -= oc1[index] * oc2[index];
            oc1[index]++;
            tot += oc1[index] * oc2[index];
        } else {
            tot -= oc1[index] * oc2[index];
            oc2[index]++;
            tot += oc1[index] * oc2[index];
        }
    }
    DynamicThing (int64_t N) {
        oc1[0] = oc2[0] = N;
        tot = N * N;
    }
};
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    map<int64_t,int64_t> row_xor;
    map<int64_t,int64_t> col_xor;
    int64_t N, K, P;
    cin >> N >> K >> P;
    DynamicThing dt(N);
    map<pair<int64_t,int64_t>,int64_t> loc;
    for (int i = 0; i < K; i++) {
        int64_t r, c, x;
        cin >> r >> c >> x;
        dt.remove(1, row_xor[r]);
        dt.remove(2, col_xor[c]);
        dt.add(1, (row_xor[r] ^= x));
        dt.add(2, (col_xor[c] ^= x));
        loc[{r, c}] = x;
    }
    while (P--) {
        int64_t r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        if (r1 != r2) {
            dt.remove(1, row_xor[r1]);
            dt.remove(1, row_xor[r2]);
            dt.add(1, row_xor[r1] ^= loc[{r1, c1}]);
            dt.add(1, row_xor[r2] ^= loc[{r1, c1}]);
        }
        if (c1 != c2) {
            dt.remove(2, col_xor[c1]);
            dt.remove(2, col_xor[c2]);
            dt.add(2, col_xor[c1] ^= loc[{r1, c1}]);
            dt.add(2, col_xor[c2] ^= loc[{r1, c1}]);
        }
        loc[{r2, c2}] = loc[{r1, c1}];
        loc[{r1, c1}] = 0;
        cout << N * N - dt.tot << '\n';
    }
}
