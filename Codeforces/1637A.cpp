#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")

using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> inp(n);
        for (int i = 0; i < n; i++) {
            cin >> inp[i];
        }
        vector<int> v = inp;
        sort(v.begin(), v.end());
        cout << ((v == inp) ? "NO\n" : "YES\n");
    }
}
