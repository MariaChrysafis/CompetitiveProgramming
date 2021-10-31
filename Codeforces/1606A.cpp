#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#define ll long long
#pragma GCC optimize("Ofast")
using namespace std;
void solve() {
    string s;
    cin >> s;
    int ab = 0;
    int ba = 0;
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == 'a' && s[i + 1] == 'b') {
            ab++;
        }
        if (s[i] == 'b' && s[i + 1] == 'a') {
            ba++;
        }
    }
    if (ab == ba) {
        cout << s << endl;
    } else {
        //cout << endl;
        if (s.back() == 'a' && ba > ab) {
            s.back() = 'b';
        }
        if (s.back() == 'b' && ab > ba) {
            s.back() = 'a';
        }
        cout << s << endl;
    }
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
