#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <set>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<int64_t> pref = {0};
    for (int i = 0; i < N; i++) {
        int x; cin >> x; pref.push_back(pref.back() + x);
    }
    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << pref[r] - pref[l] << '\n';
    }
}
