#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;
int moves1 (char c, set<char> s) {
    for (int i = 0; i <= 26; i++) {
        if (s.count(c)) {
            return i;
        }
        if (c == 'a') c = 'z';
        else c--;
    }
}
int moves2 (char c, set<char> s) {
    for (int i = 0; i <= 26; i++) {
        if (s.count(c)) {
            return i;
        }
        if (c == 'z') c = 'a';
        else c++;
    }
}
int solve () {
    string s1, s2;
    cin >> s1 >> s2;
    set<char> mySet;
    for (int i = 0; i < s2.length(); i++) {
        mySet.insert(s2[i]);
    }
    map<char,int> myMap;
    for (char c = 'a'; c <= 'z'; c++) {
        myMap[c] = min(moves1(c, mySet), moves2(c, mySet));
    }
    int ans = 0;
    for (int i = 0; i < s1.length(); i++) {
        ans += myMap[s1[i]];
    }
    return ans;
}
int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int x = solve();
        cout << "Case #" << tc << ": " << x << '\n';
    }
}
