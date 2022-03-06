#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    int64_t myMin = 0;
    int64_t ans = -1e10;
    int64_t pref = 0;
    for (int i = 1; i <= N; i++) {
        int64_t x; cin >> x;
        pref += x;
        ans = max(ans, pref - myMin);
        myMin = min(myMin, pref);
    }
    cout << ans;
}
