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
class XOR_Vector_Space {
public:
    XOR_Vector_Space() {

    }
    void add_int (int x) {
        for (int i: basis) {
            x = min(x, x ^ i);
        }
        if (x != 0) basis.push_back(x);
    }
    vector<int> basis;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        XOR_Vector_Space xvs;
        int K, M;
        cin >> K >> M;
        while (M--) {
            int x; cin >> x;
            xvs.add_int(x);
        }
        cout << (1 << (K - xvs.basis.size())) << '\n';
    }
}
