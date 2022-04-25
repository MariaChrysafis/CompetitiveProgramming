#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int arr[n];
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        arr[i] = 0;
        for (int j = 0; j < k; j++) {
            arr[i] += (1 << j) * (s[j] == '1');
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min(ans, __builtin_popcount(arr[i] ^ arr[j]));
        }
    }
    cout << ans;
}
