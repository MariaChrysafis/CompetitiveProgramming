#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
using namespace std;

typedef int64_t ll;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (s.length() == 1) {
        cout << s + s << '\n';
        return;
    }
    if (s[0] == s[1]) {
        cout << s[0] << s[0] << '\n';
        return;
    }
    string str = "";
    for (int i = 0; i < s.length(); i++) {
        if (i == 0 || s[i] <= s[i - 1]) {
            str += s[i];
        } else {
            break;
        }
    }
    string str1 = "";
    str1 = str;
    reverse(str.begin(), str.end());
    cout << str1 + str << '\n';
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
