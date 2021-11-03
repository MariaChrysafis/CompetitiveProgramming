#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
int main() {
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> arr(n);
    long long myMin[n + 1];
    long long myMax[n + 1];
    for (long long i = 0; i <= n; i++) {
        myMin[i] = (long long)1e8;
        myMax[i] = -1;
    }
    set<long long> s;
    for (long long i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] == 0) {
            continue;
        }
        s.insert(arr[i]);
        myMin[arr[i]] = min(myMin[arr[i]], i);
        myMax[arr[i]] = max(myMax[arr[i]], i);
    }
    int interval[2 * n + 3];
    for (long long i = 0; i <= 2 * n + 2; i++) {
        interval[i] = 0;
    }
    for (long long i: s) {
        interval[myMin[i] * 2]++;
        interval[myMax[i] * 2 + 1]--;
    }
    long long a = 0;
    long long ans = 0;
    for (long long i = 0; i <= 2 * n + 2; i++) {
        ans += interval[i];
        interval[i] = ans;
        a = max(a, ans);
    }
    for (int i: s) {
        if (myMin[i] == myMax[i]) {
            continue;
        }
        if (interval[2 * myMin[i]] - 1 != interval[2 * myMax[i] + 1]) {
            cout << -1;
            return 0;
        }
        //cout << interval[2 * myMin[i]] << " " << interval[2 * myMax[i] + 1] << endl;
    }
    cout << a;
}
