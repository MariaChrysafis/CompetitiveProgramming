#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<int> v(n);
    ll sum = 0; ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        sum += v[i];
        ans = min(ans + v[i]/2, sum/3);
    }
    cout << ans;
}
