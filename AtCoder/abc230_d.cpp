#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

void solve() {
    ll N, D;
    cin >> N >> D;
    vector<pair<ll,ll>> vec(N);
    for (int i = 0; i < vec.size(); i++) {
        cin >> vec[i].first >> vec[i].second;
        swap(vec[i].first, vec[i].second);
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        swap(vec[i].first, vec[i].second);
    }
    set<int> taken;
    for (int i = 0; i < vec.size(); i++) {
        auto it = taken.lower_bound(vec[i].first - D + 1);
        if (it != taken.end() ) {
            int x = *it;
            if (x + D - 1 >= vec[i].first) {
                continue;
            }
        }

        taken.insert(vec[i].second);
    }
    cout << taken.size() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
