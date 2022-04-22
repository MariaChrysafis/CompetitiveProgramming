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
        vector<int> arr(n);
        set<int> s1[2];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            s1[i % 2].insert(arr[i] % 2);
        }
        if (s1[0].size() == 1 && s1[1].size() == 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
