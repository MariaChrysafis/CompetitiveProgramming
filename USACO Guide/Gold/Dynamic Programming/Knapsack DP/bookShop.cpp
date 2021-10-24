#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
int main() {
    int n, x;
    cin >> n >> x;
    int dp[x + 1];
    for (int i = 0; i <= x; i++) {
        dp[i] = -(int)1e7;
    }
    dp[0] = 0;
    vector<int> price(n), pages(n);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = x; j >= price[i]; j--) {
            dp[j] = max(dp[j], dp[j - price[i]] + pages[i]);
            myMax = max(myMax, dp[j]);
        }
    }
    cout << myMax;
}
