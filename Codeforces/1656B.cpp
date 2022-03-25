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
    int N, K;
    cin >> N >> K;
    vector<int> arr(N);
    set<int> s;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
    }
    for (int i = 0; i < N; i++) {
        if (s.count(arr[i] + K)) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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
