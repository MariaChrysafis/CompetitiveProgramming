#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int a = 0, b = 0;
        for (int i = 0; i < 6; i++) {
            if (i < 3) a += s[i];
            else b += s[i];
        }
        if (a == b) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
