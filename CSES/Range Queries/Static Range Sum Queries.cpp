#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<int64_t> pref(N + 1);
    pref[0] = 0;
    for (int i = 1; i <= N; i++) {
        int64_t x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }
    while (Q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << pref[r + 1] - pref[l] << '\n';
    }
}
