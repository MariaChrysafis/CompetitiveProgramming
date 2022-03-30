#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
 
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t n, x;
    cin >> n >> x;
    vector<int64_t> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int64_t> pref = {0};
    map<int64_t,int64_t> myMap;
    for (int i = 1; i <= n; i++) {
        pref.push_back(pref.back() + arr[i - 1]);
    }
    int64_t ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += myMap[-x + pref[i]];
        myMap[pref[i]]++;
    }
    cout << ans;
}
