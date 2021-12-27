#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
using namespace std;

bool solve () {
    int x, y, z;
    cin >> x >> y >> z;
    if (x + z == y || x + y == z || y + z == x) {
        return true;
    }
    if (x == y && z % 2 == 0) {
        return true;
    }
    if (y == z && x % 2 == 0) {
        return true;
    }
    if (x == z && y % 2 == 0) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        bool b = solve();
        if (b) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

}
