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
int main() {
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);
    int n;
    cin >> n;
    int t;
    cin >> t;
    vector<ll> v;
    for (int i = 0; i < n; i++) {
        ll speed, position;
        cin >> position >> speed;
        v.push_back(speed * t + position);
    }
    multiset<ll> s;
    s.insert(v[0]);
    for (int i = 1; i < n; i++) {
        auto it = s.lower_bound(v[i]);
        if (it == s.begin()) {
            s.insert(v[i]);
        } else {
            it--;
            s.erase(it);
            s.insert(v[i]);
        }
    }
    cout <<s.size()<< endl;
}
