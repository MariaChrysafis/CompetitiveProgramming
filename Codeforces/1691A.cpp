#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll long long
#include <map>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int cnt[2];
        cnt[0] = cnt[1] = 0;
        for (int i = 0; i < n; i++) {
            int x; cin >>x ;
            cnt[x % 2]++;
        }
        cout << min(cnt[0], cnt[1]) << '\n';
    }
}
