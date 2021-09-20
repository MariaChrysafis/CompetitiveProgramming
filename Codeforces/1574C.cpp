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
    int n;
    cin >> n;
    vector<long long> a(n);
    set<long long> ms;
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        ms.insert(a[i]);
    }
    sort(a.begin(), a.end());
    int m;
    cin >> m;
    while(m--) {
        long long x, y;
        cin >> x >> y;
        long long myMin = 1e20;
        auto it = ms.lower_bound(x);
        if(it != ms.end()) myMin = min(myMin, max(y - (sum - *it), 0ll));
        it--;
        myMin = min(max(x - *it, 0ll) + max(y - (sum - *it), 0ll), myMin);
        cout << myMin << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
