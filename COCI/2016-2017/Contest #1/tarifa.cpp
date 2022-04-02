#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>
 
using namespace std;
 
const int MOD = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t x, n;
    cin >> x >> n;
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        sum += x; int64_t a; cin >> a; sum -= a;
    }
    cout << sum + x << '\n';
}
