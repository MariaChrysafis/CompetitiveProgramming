#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

bool isPalindrome (string s) {
    reverse(s.begin(), s.end());
    string str = s;
    reverse(s.begin(), s.end());
    return (str == s);
}

string ts (char c) {
    string s = "";
    s += c;
    return s;
}

void solve () {
    int n;
    cin >> n;
    vector<string> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    for (int i = 0; i < n; i++) {
        if (isPalindrome(vec[i])) {
            cout << "YES\n";
            return;
        }
    }
    map<string,bool> oc;
    for (int i = 0; i < n; i++) {
        oc[vec[i]] = true;
        if (vec[i].size() == 2 && oc[ts(vec[i][1]) + vec[i][0]]) {
            cout << "YES\n";
            return;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            if (vec[i].size() == 2 && oc[ts(vec[i][1]) + vec[i][0] + c]) {
                cout << "YES\n";
                return;
            }
        }
        if (vec[i].size() == 3 && oc[ts(vec[i][2]) + vec[i][1]]) {
            cout << "YES\n";
            return;
        }
        if (vec[i].size() == 3 && oc[ts(vec[i][2]) + vec[i][1] + vec[i][0]]) {
            cout << "YES\n";
            return;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            if (vec[i].size() == 3 && oc[ts(vec[i][2]) + vec[i][1] + vec[i][0] + c]) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
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
