#include <bits/stdc++.h>
using namespace std;
bool solve () {
    int a, b, c, x, y;
    cin >> a >> b >> c >> x >> y;
    if (a + b + c < x + y) {
        return false;
    }
    if (a + c < x) {
        return false;
    }
    if (b + c < y) {
        return false;
    }
    return true;
}
int main() {
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
