#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
    int T, A, B;
    cin >> T >> A >> B;
    bool canAchieve[T + 1];
    canAchieve[0] = true;
    for (int i = 1; i <= T; i++) {
        canAchieve[i] = false;
        if (i >= A) canAchieve[i] = canAchieve[i] || canAchieve[i - A];
        if (i >= B) canAchieve[i] = canAchieve[i] || canAchieve[i - B];
    }
    for (int i = 1; i <= T; i++) {
        if(canAchieve[i]) {
            canAchieve[i/2] = true;
        }
    }
    for (int i = 1; i <= T; i++) {
        if (i >= A) canAchieve[i] = canAchieve[i] || canAchieve[i - A];
        if (i >= B) canAchieve[i] = canAchieve[i] || canAchieve[i - B];
    }
    for (int i = T; i >= 0; i--) {
        //cout << canAchieve[i] << " ";
        if (canAchieve[i]) {
            cout << i;
            return 0;
        }
    }
}
