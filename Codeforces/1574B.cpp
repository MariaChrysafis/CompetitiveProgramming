/*
1 1 1 0
1 1 1 1
1 1 2 0
1 2 1 0
2 1 1 0
1 1 1 2
1 1 2 1
1 1 3 0
1 2 1 1
1 2 2 0
1 3 1 0
2 1 1 1
2 1 2 0
2 2 1 0
3 1 1 0
1 1 1 3
1 1 2 2
1 1 3 1
1 1 4 0
1 2 1 2
1 2 2 1
1 2 3 0
1 3 1 1
1 3 2 0
1 4 1 0
2 1 1 2
2 1 2 1
2 1 3 0
2 2 1 1
2 2 2 0
2 3 1 0
3 1 1 1
3 1 2 0
3 2 1 0
4 1 1 0
1 1 1 4
1 1 2 3
1 1 3 2
1 1 4 1
1 1 5 0
1 2 1 3
1 2 2 2
1 2 3 1
1 2 4 0
1 3 1 2
1 3 2 1
1 3 3 0
1 4 1 1
1 4 2 0
1 5 1 0
2 1 1 3
2 1 2 2
2 1 3 1
2 1 4 0
2 2 1 2
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

void solve() {
    long long a, b, c;
    cin >> a >> b >> c;
    vector<long long> v = {a, b, c};
    sort(v.begin(), v.end());
    a = v[v.size() - 1], b = v[v.size() - 2], c = v[v.size() - 3];
    long long x = a - 1 + b - 1 + c - 1;
    long long m;
    cin >> m;
    if(m > x) {
        cout << "NO\n";
        return;
    }
    if(a <= (a + b + c + 1)/2) {
        cout << "YES\n";
        return;
    }
    long long cntr = 0;
    long long len = a + b + c;
    a -= (a + b + c + 1)/2;
    cntr += 2 * a;
    if(len % 2 == 0) cntr--;
    if(m < cntr) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
