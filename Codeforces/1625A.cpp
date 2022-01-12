#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

void solve () {
    int N, L;
    cin >> N >> L;
    int arr[N];
    bool bits[L][N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        for (int j = 0; j < L; j++) {
            bits[j][i] = (bool)(arr[i] & (1 << j));
        }
    }
    int ans = 0;
    for (int i = 0; i < L; i++) {
        int cntr = 0;
        for (int j = 0; j < N; j++) {
            if (bits[i][j]) cntr++;
            else cntr--;
        }
        if (cntr > 0) {
            ans += (1 << i);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
