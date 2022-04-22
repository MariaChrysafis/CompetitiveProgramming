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
        vector<int> arr(n); map<int,int> cnt;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            cnt[arr[i]]++;
        }
        bool f = false;
        for (auto& p: cnt) {
            if (p.second >= 3) {
                cout << p.first << '\n';
                f = true;
                break;
            }
        }
        if (!f) {
            cout << "-1\n";
        }
    }
}
