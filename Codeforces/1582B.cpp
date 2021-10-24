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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> arr(n);
        long long cnt1 = 0;
        long long powr = 1;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            if (arr[i] == 1) {
                cnt1++;
            } else if (arr[i] == 0) {
                powr *= 2;
            }
        }
        cout << cnt1 * powr << endl;
    }
}
