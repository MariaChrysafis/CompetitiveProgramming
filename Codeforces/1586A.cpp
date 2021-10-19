#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#define ll int
using namespace std;
bool composite(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return true;
        }
    }
    return false;
}
void print(vector<int> v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << endl;
}
void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ans += arr[i];
    }
    if (composite(ans)) {
        cout << n << endl;
        for (int j = 0; j < n; j++) {
            cout << j + 1 << " ";
        }
        cout << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 1) {
            cout << n - 1 << endl;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    cout << j + 1 << " ";
                }
            }
            cout << endl;
            return;
        };
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
