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
    vector<int64_t> v(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        b[v[i] - 1] = i;
    }
    int ans = 1;
    for (int i = 1; i < n; i++) {
        ans += (b[i] < b[i - 1]);
    }
    cout << ans;
}
