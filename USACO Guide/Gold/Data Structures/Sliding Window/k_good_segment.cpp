#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int l = 0;
    int r = 0;
    map<int,int> oc;
    int sz = 1;
    oc[arr[0]]++;
    int best[n];
    for (int i = 0; i < n; i++) {
        best[i] = i;
    }
    while (l - 1 <= r) {
        best[l] = r;
        if (r == n - 1) {
            l++;
            continue;
        }
        if (oc[arr[r + 1]]) {
            r++;
            oc[arr[r]]++;
            continue;
        }
        if (!oc[arr[r + 1]]) {
            if (sz + 1 <= k) {
                sz++, r++;
                oc[arr[r]]++;
                continue;
            }
        }
        oc[arr[l]]--;
        if (oc[arr[l]] == 0) {
            sz--;
        }
        l++;
    }
    long long ans = 0;
    int myMax = 0;
    int good = 0;
    for (int i = 0; i < n; i++) {
        if (best[i] - i + 1 > myMax) {
            myMax = best[i] - i + 1;
            good = i;
        }
        ans += best[i] - i + 1;
    }
    cout << good + 1 << " " << best[good] + 1;
}
