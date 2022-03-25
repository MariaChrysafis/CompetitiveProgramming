#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>

using namespace std;
void solve () {
    int N; cin >> N;
    vector<int> v(N);
    set<int> s;
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        s.insert(v[i]);
    }
    if (!s.count(1)) {
        cout << "YES\n";
        return;
    }
    for (int i = 0; i < N; i++) {
        if (s.count(v[i] + 1)) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }

}
