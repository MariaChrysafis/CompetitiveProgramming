#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    int n;
    cin >> n;
    if ((n * (n + 1)/2) % 2 != 0) {
        cout << 0;
        return 0;
    }
    long long cnt[n * n];
    for (int i = 0; i <= n * n; i++) {
        cnt[i] = 0;
    }
    cnt[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = n * n; j >= 0; j--) {
            if (j - i < 0) continue;
            cnt[j] += cnt[j - i];
            cnt[j] %= MOD;
        }
    }
    cout << (cnt[n * (n + 1)/4] * (MOD + 1)/2) % MOD;
}
