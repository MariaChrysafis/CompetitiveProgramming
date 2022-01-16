#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;
static const int MAX = 1e7 + 1;

const int MOD = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll d[MAX];
    d[1] = 0;
    d[2] = 1;
    for (int i = 3; i < MAX; i++) {
        d[i] = ((i - 1) * (d[i - 1] + d[i - 2]) % MOD) % MOD;
    }
    int T;
    cin >> T;
    while (T--) {
        int x;
        cin >> x;
        cout << d[x] << '\n';
    }
}
