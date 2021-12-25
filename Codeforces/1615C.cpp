#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

typedef long long ll;
using namespace std;

int overlap (string s1, string s2) {
    int cntr = 0;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            cntr++;
        }
    }
    return cntr;
}

string flip (string s) {
    string str;
    for (char c: s) {
        if (c == '0') str += '1';
        else str += '0';
    }
    return str;
}

string fix (string s, int ind) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1') s[i] = '0';
        else s[i] = '1';
    }
    s[ind] = '1';
    return s;
}

int cost_even (string a, string b) {
    map<pair<char,char>,int> myMap;
    for (int i = 0; i < a.length(); i++) {
        myMap[{a[i] - '0', b[i] - '0'}]++;
    }
    int ans = 1e9;
    if (myMap[{1, 0}] == myMap[{0, 1}]) {
        ans = min(ans, 2 * myMap[{1, 0}]);
    }
    return ans;
}

int cost_odd (string s, string b) {
    set<pair<int,int>> mySet;
    int myMin = 1e9;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1' && !mySet.count({s[i] - '0', b[i] - '0'})) {
            myMin = min(myMin, cost_even(fix(s, i), b) + 1);
            mySet.insert({s[i] - '0', b[i] - '0'});
        }
    }
    return myMin;
}

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        int ans = min(cost_odd(a, b), cost_even(a, b));
        if (ans == 1e9) {
            cout << "-1\n";
            continue;
        }
        cout << ans << '\n';
    }

}
