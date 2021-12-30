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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, W;
    cin >> N >> W;
    pair<ll,ll> item[N];
    for (int i = 0; i < N; i++) {
        cin >> item[i].first >> item[i].second;
    }
    sort(item, item + N);
    for (int i = 0; i < N/2; i++) {
        swap(item[i], item[N - i - 1]);
    }
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        while (W >= 1 && item[i].second >= 1) {
            W--;
            ans += item[i].first;
            item[i].second--;
        }
    }
    cout << ans << '\n';
}
