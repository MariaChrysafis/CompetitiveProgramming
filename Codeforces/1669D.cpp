#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s; cin >> s;
        vector<string> vec = {""};
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'W') {
                if (vec.back().size() != 0) vec.emplace_back();
            } else {
                vec.back().push_back(s[i]);
            }
        }
        bool fine = true;
        for (auto& str: vec) {
            set<char> mySet;
            for (char c: str) mySet.insert(c);
            if (mySet.size() == 1) {
                fine = false;
            }
        }
        if (fine) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
