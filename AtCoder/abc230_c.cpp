#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

void solve() {
    ll N, A, B, P, Q, R, S;
    cin >> N >> A >> B >> P >> Q >> R >> S;
    for (ll i = P; i <= Q; i++) {
        for (ll j = R; j <= S; j++) {
            if (i - j != A - B && i + j != A + B) {
                cout << '.';
                continue;
            }
            cout << '#';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
