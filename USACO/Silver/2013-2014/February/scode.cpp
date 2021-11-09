#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll int
#include <map>

using namespace std;
map<string,int> myMap;
string sub (string s, int l, int r) {
    string str = "";
    for (int i = l; i <= r; i++) {
        str += s[i];
    }
    return str;
}
int rec (string s) {
    if (myMap[s]) {
        return myMap[s];
    }
    int ans = 1;
    for (int i = 0; i < (s.length() - 1)/2; i++) {
        if (sub(s, 0, i) == sub(s, s.length() - i - 1, s.length() - 1)) {
            ans += rec(sub(s, 0, s.length() - i - 2));
            ans += rec(sub(s, i + 1, s.length() - 1));
        }
    }
    for (int len = 1; len < (s.length() + 1)/2; len++) {
        if (sub(s, 0, len - 1) == sub(s, len, 2 * len - 1)) {
            ans += rec(sub(s, len, s.length() - 1));
        }
    }
    for (int len = 1; len < (s.length() + 1)/2; len++) {
        if (sub(s, s.length() - len, s.length() - 1) == sub(s, s.length() - 2 * len, s.length() - len - 1)) {
            ans += rec(sub(s, 0, s.length() - len - 1));
        }
    }
    ans %= 2014;
    return (myMap[s] = ans);
}
int main() {
    freopen("scode.in", "r", stdin);
    freopen("scode.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    cout << (rec(s) + 2013) % 2014;
}
