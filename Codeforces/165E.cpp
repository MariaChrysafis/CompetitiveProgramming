#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;
const int MAX = 22;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    a[0] = -1;
    vector<int> dp;
    dp.assign((1 << MAX), 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[a[i]] = i;
    }
    for (int i = 0; i < dp.size(); i++) {
        if (dp[i]) {
            continue;
        }
        for (int j = 0; j < MAX; j++) {
            if (i & (1 << j)) {
                if (dp[i - (1 << j)] != 0) {
                    dp[i] = dp[i - (1 << j)];
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << a[dp[(1 << MAX) - 1 - a[i]]] << ' ';
    }

}
