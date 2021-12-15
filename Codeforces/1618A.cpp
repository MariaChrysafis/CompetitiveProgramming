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
vector<ll> generate (ll x, ll y, ll z) {
    vector<ll> v;
    v.push_back(x), v.push_back(y), v.push_back(z);
    v.push_back(x + y), v.push_back(x + z), v.push_back(y + z);
    v.push_back(x + y + z);
    sort(v.begin(), v.end());
    return v;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        vector<ll> arr(7);
        ll sum = 0;
        for (int i = 0; i < 7; i++) {
            cin >> arr[i];
            sum += arr[i];
        }
        sum /= 4;
        ll x = arr[0];
        ll y1 = arr[1] - arr[0];
        ll y2 = arr[1];
        ll z1 = sum - x - y1;
        ll z2 = sum - x - y2;
        if (generate(x, y1, z1) == arr) {
            cout << x << " " << y1 << " " << z1 << '\n';
        } else {
            cout << x << " " << y2 << " " << z2 << '\n';
        }

    }
}
