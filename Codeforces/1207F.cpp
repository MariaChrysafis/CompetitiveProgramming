#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <functional>
#include <queue>
#include <list>
#include <set>
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 500001;
    const int sz = sqrt(n);
    int ans[(int)sqrt(n)][(int)sqrt(n)]; //ans[i][j] means that it is j modulo i
    for (int i = 0; i < (int)sqrt(n); i++) {
        for (int j = 0; j < (int)sqrt(n); j++) {
            ans[i][j] = 0;
        }
    }
    vector<int> v;
    v.assign(n + 1, 0);
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        int x, y;
        cin >> x >> y;
        if (t == 2) {
            // print something
            //y modulo x
            if (x >= sz) {
                int res = 0;
                for (int i = y; i <= n; i += x) {
                    res += v[i];
                }
                cout << res << '\n';
            } else {
                cout << ans[x][y] << '\n';
            }
        } else {
            //cout << x << endl;
            v[x] += y;
            for (int i = 1; i < sz; i++) {
                //cout << x << " " << i << " " << x % i << endl;
                if (x % i < sz) {
                    ans[i][x % i] += y;
                }
            }
        }
    }
}
