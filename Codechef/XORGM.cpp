#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;
bool same (vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return (a == b);
}
void solve () {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    int axor = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        axor ^= a[i];
    }
    int bxor = 0;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        bxor ^= b[i];
    }
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = axor ^ (bxor ^ a[i]);
        //cout << c[i] << ' ';
    }
    if (!same(b, c)) {
        cout << "-1\n";
        return;
    }
    //cout << '\n';
    for (int i: c) {
        cout << i << ' ';
    }
    cout << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
