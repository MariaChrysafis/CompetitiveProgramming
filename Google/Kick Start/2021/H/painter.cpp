#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;
int cost (vector<int> v) {
    int prev = -2;
    int cntr = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != prev + 1) {
            cntr++;
        }
        prev = v[i];
    }
    return cntr;
}
int solve () {
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char,vector<int>> myMap;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'R') {
            myMap['R'].push_back(i);
        } else if (s[i] == 'Y') {
            myMap['Y'].push_back(i);
        } else if (s[i] == 'B') {
            myMap['B'].push_back(i);
        } else if (s[i] == 'O') {
            myMap['Y'].push_back(i);
            myMap['R'].push_back(i);
        } else if (s[i] == 'P') {
            myMap['B'].push_back(i);
            myMap['R'].push_back(i);
        } else if (s[i] == 'G') {
            myMap['B'].push_back(i);
            myMap['Y'].push_back(i);
        } else if (s[i] == 'A'){
            myMap['R'].push_back(i);
            myMap['B'].push_back(i);
            myMap['Y'].push_back(i);
        }
    }
    vector<char> primary_colors = {'R', 'B', 'Y'};
    int ans = 0;
    for (char c: primary_colors) {
        ans += cost(myMap[c]);
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
