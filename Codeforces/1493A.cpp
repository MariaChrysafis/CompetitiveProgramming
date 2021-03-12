#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
void solve(int n, int k) {
    bool arr[k + 1];
    for (int i = 0; i <= k; i++) {
        arr[i] = false;
    }
    arr[0] = 1;
    vector<int> ans;
    for (int i = n; i >= 1; i--) {
        if (i == k) {
            continue;
        }
        if (i > k) {
            ans.push_back(i);
            continue;
        }
        bool fine = true;
        for (int j = 0; j < k; j++) {
            if (arr[j] && i + j == k) {
                fine = false;
            }
        }
        if (fine) {
            ans.push_back(i);

            for (int j = 0; j < k; j++) {
                if (arr[j] && i + j <= k) {
                    arr[i + j] = true;
                }
            }
        }

        /// cout << cntr << endl;
    }
    cout << ans.size() << endl;
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        solve(n, k);
    }
}
