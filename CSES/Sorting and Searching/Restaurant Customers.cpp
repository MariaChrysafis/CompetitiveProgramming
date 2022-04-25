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
    vector<pair<int,bool>> vec;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        vec.emplace_back(x, false);
        vec.emplace_back(y, true);
    }
    sort(vec.begin(), vec.end());
    int ans = 0;
    int res = 0;
    for (auto& p: vec) {
        if (p.second == true) ans--;
        else ans++;
        res = max(res, ans);
    }
    cout << res;
}
