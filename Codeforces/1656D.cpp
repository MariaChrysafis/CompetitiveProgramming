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
    int64_t N; cin >> N;
    if (N == 2 || N == 4) {
        cout << "-1\n";
        return;
    }
    for (int64_t i = 2; i != 0; i *= 2) {
        if (i * (i + 1)/2 > N) {
            break;
        }
        if (N % i == i/2) {
            cout << i << '\n';
            return;
        }
    }
    for (int64_t i = 2; i != 0; i *= 2) {
        if (N % i != 0) {
            if (N/(i/2) == 1) {
                cout << "-1\n";
                return;
            }
            cout << N/(i/2) << '\n';
            return;
            break;
        }
    }
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
