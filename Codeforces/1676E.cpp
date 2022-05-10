#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<int> pref;
        pref.push_back(0);
        vector<int> a;
        int x = 0;
        for (int i = 0; i < n; i++) {
            cin >> x;
            a.push_back(x);
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        for (int i: a) {
            pref.push_back(pref.back() + i);
        }
        while (q--) {
            int y;
            cin >> y;
            if (pref.back() < y) {
                cout << -1 << '\n';
                continue;
            }
            int l = 0;
            int r = (int)pref.size() - 1;
            while (l != r) {
                int m = (l + r)/2;
                if (pref[m] >= y) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            cout << l << '\n';
        }
    }
}
