#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#define pb push_back
#define mp make_pair

#define ll long long
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<ll> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        sort(v.begin(), v.end());
        map<int,bool> marked;
        ll ans = 0;
        for (int i = n - 1; i >= n - k; i--) {
            marked[i] = true;
            for (int j = n - k - 1; j >= 0; j--) {
                if (marked[j]) continue;
                marked[j] = true;
                ans += v[j]/v[i];
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            ans += !marked[i] * v[i];
        }
        cout << ans << '\n';
    }


}
