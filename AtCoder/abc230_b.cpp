#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

void solve() {
    string s;
    cin >> s;
    if (s == "o" || s == "x" || s == "ox" || s == "xo" || s == "xx") {
        cout << "Yes\n";
        return;
    }
    int st = -1;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'o') {
            st = i;
            break;
        }
    }
    if (st == -1 || st >= 3) {
        cout << "No\n";
        return;
    }
    for (int i = st; i < s.length(); i++) {
        if ((i - st) % 3 == 0) {
            if (s[i] != 'o') {
                cout << "No\n";
                return;
            }
        } else {
            if (s[i] != 'x') {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
