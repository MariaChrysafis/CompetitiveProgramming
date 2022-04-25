#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int64_t arr[n];
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sum += arr[i];
    }
    int64_t ans = sum;
    for (int i = 0; i < (1 << n); i++) {
        int64_t x = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                x += arr[j];
            }
        }
        ans = min(ans, abs(sum - 2 * x));
    }
    cout << ans;
}
