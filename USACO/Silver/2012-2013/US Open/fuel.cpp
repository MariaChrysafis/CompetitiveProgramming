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

typedef long long ll;
const int MOD = 1e9 + 7;
using namespace std;

int main() {
    freopen("fuel.in", "r", stdin);
    freopen("fuel.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, G, B, D;
    cin >> N >> G >> B >> D;
    vector<pair<ll,ll>> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    vec.push_back({D, 0});
    sort(vec.begin(), vec.end());
    ll fuel = B;
    ll ans = 0;
    for (int i = 0; i < vec.size(); i++) {
        //cout << ans << " " << fuel << '\n';
        if (i != 0) fuel -= abs(vec[i - 1].first - vec[i].first);
        else fuel -= abs(vec[i].first);
        if (fuel < 0) {
            cout << "-1\n";
            return 0;
        }
        ll nxt = -1;
        for (int j = i + 1; j < vec.size(); j++) {
            if (vec[j].second < vec[i].second) {
                nxt = j;
                break;
            }
        }
        if (nxt == -1) {
            break;
        }
        if (abs(vec[nxt].first - vec[i].first) <= fuel) {
            //if we can visited our next thing, so continue
            continue;
        } else {
            //we cannot visit our next "good" station, so we need to stop for fuel somewhere (namely here!)
            ll fuelNeeded = abs(vec[i].first - vec[nxt].first);
            fuelNeeded = min(fuelNeeded - fuel, G - fuel);
            fuel += fuelNeeded;
            ans += fuelNeeded * vec[i].second;
        }
    }
    cout << ans << '\n';

}
