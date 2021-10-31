#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
void solve() {
    int n;
    cin >> n;
    vector<ll> arr(n + 1);
    ll myMax = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        myMax = max(myMax, arr[i] - i);
    }
    cout << myMax << '\n';
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
