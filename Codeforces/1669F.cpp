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
        vector<int> arr(n), pref = {0}, suf(n + 1);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            pref.push_back(pref.back() + arr[i]);
        }
        suf[n] = 0;
        map<int,int> myMap;
        myMap[0] = n;
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = suf[i + 1] + arr[i];
            myMap[suf[i]] = i;
        }
        int myMax = 0;
        for (int l = 0; l <= n; l++) {
            if (pref[l] * 2 > pref.back()) {
                break;
            }
            if (myMap.count(pref[l])) {
                //cout << l << ' ' << n - myMap[pref[l]] << '\n';
                myMax = max(myMax, l + n - myMap[pref[l]]);
            }
        }
        cout << myMax << '\n';
    }
}
