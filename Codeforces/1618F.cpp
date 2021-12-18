#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
typedef long long ll;

using namespace std;

ll powr (ll x) {
    ll ans = 1;
    for (int i = 0; i < x; i++) {
        ans *= 2;
    }
    return ans;
}

string to_binary (ll x) {
    string str = "";
    for (int i = 60; i >= 0; i--) {
        if (x & powr(i)) {
            str += '1';
        } else {
            str += '0';
        }
    }
    while (str[0] == '0') {
        str = str.substr(1, str.length() - 1);
    }
    return str;
}

string rev (string s) {
    reverse(s.begin(), s.end());
    return s;
}

bool isSubstring (string s1, string s2) {
    for (int i = 0; i < s1.length(); i++) {
        bool fine = true;
        for (int j = 0; j < s2.length(); j++) {
            if (i + j == s1.length()) {
                fine = false;
                break;
            }
            if (s1[i + j] != s2[j]) {
                fine = false;
            }
        }
        if (fine) {
            return true;
        }
    }
    return false;
}

string rem (string s) {
    while (s[0] == '0') {
        s = s.substr(1, s.length() - 1);
    }
    return s;
}

string rem1 (string s) {
    while (s.back() == '0') {
        s.pop_back();
    }
    return s;
}

map<string,int> hv;

bool valid (string& s1, string s2) {
    s2 = rem(s2);
    if (hv[s2] == 1) {
        return false;
    }
    hv[s2] = 1;
    if (s1 == s2) {
        return true;
    }
    if (!isSubstring(s1, rem1(s2)) && !isSubstring(s1, rem1(rem(rev(s2))))) {
        return false;
    }
    if (valid(s1, "1" + rev(s2))) {
        hv[s2] = 1;
        return true;
    }
    if (valid(s1, "0" + rev(s2))) {
        hv[s2] = 1;
        return true;
    }
    hv[s2] = 2;
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll x, y;
    cin >> x >> y;
    string s1 = to_binary(y); //s1 is larger
    string s2 = to_binary(x); //s2 is smaller
    //cout << s1 << " " << s2 << '\n';
    if (!valid(s1, s2)) {
        cout << "NO";
    } else {
        cout << "YES";
    }

}
