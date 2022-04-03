#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>
 
using namespace std;
 
const int MX = (1 << 20);
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> dp1(MX), mp(MX);
    for (int i = 0; i < n; i++) {
        dp1[arr[i]]++, mp[arr[i]]++;
    }
    for (int i = 0; i < log2(MX); i++) {
        for (int mask = 0; mask < MX; mask++) {
            if (mask & (1 << i)) {
                dp1[mask] += dp1[mask ^ (1 << i)];
            }
        }
    }
    vector<int> dp2(MX);
    dp2 = mp;
    for (int i = 0; i < log2(MX); i++) {
        for (int mask = 0; mask < MX; mask++) {
            if ((mask ^ (1 << i)) != mask - (1 << i)) {
                dp2[mask] += dp2[mask ^ (1 << i)];
            }
        }
    }
    for (int i = 0; i < arr.size(); i++) {
        cout << dp1[arr[i]] << " " << dp2[arr[i]] << " " << n - dp1[MX - 1 - arr[i]] << '\n';
    }
}
