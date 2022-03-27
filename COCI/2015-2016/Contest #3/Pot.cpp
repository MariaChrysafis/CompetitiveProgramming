#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>
 
using namespace std;
long long binPow (long long x, long long y) {
    if (y == 0) {
        return 1;
    }
    return x * binPow(x, y - 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<string> vec(n);
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        char c = vec[i].back();
        vec[i].pop_back();
        ans += binPow(stoll(vec[i]), c - '0');
    }
    cout << ans;
}
