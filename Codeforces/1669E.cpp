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
        map<string,int64_t> myMap;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string s; cin >> s; myMap[s]++;
        }
        int64_t ans = 0;
        for (auto& p: myMap) {
            string s = p.first;
            for (int i = 0; i < s.length(); i++) {
                char orig = s[i];
                for (char c = 'a'; c <= 'k'; c++) {
                    if (c == orig) continue;
                    s[i] = c;
                    if (myMap.count(s)) {
                        ans += myMap[s] * p.second;
                        //cout << s << '\n';
                    }
                }
                s[i] = orig;
            }
            //cout << '\n';
        }
        cout << ans/2 << '\n';
    }
}
