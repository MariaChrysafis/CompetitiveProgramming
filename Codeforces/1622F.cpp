#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <set>
#include <algorithm>
#include <random>
using namespace std;

bool psq (int x) {
    return ((int)sqrt(x) * (int)sqrt(x) == x);
}

void solve(int n) {
    int64_t reduce[n + 1];
    for (int i = 0; i <= n; i++) {
        reduce[i] = -1;
    }
    for (int i = 1; i <= n; i++) {
        if (reduce[i] == -1) {
            reduce[i] = i;
            for (int j = i; j <= n; j += i) {
                if (psq(j/i)) {
                    reduce[j] = reduce[i];
                }
            }
        }
    }
    int64_t c[n + 1];
    mt19937_64 rng((int64_t) chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i <= n; i++) {
        c[i] = rng();
        //cout << c[i] << ' ';
    }
    vector<int64_t> primes(n + 1);
    vector<bool> vis(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            primes[i] = c[i];
            for (int j = 2 * i; j <= n; j += i) {
                int x = j;
                while (x % i == 0) {
                    x /= i;
                    primes[j] ^= c[i];
                    vis[j] = true;
                }
            }
        }
    }
    set<int64_t> pos;
    for (int i = 1; i <= n; i++) {
        primes[i] = primes[i] ^ primes[i - 1];
        pos.insert(primes[i]);
    }
    int64_t tot = 0;
    for (int i = 1; i <= n; i++) {
        tot ^= primes[i];
    }
    if (tot == 0) {
        cout << n << '\n';
        for (int j = 1; j <= n; j++) {
            cout << j << " ";
        }
        cout << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (primes[i] == tot) {
            cout << n - 1 << '\n';
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    cout << j << ' ';
                }
            }
            return;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (pos.count(tot ^ primes[i])) {
            bool taken = false;
            cout << n - 2 << '\n';
            for (int j = 1; j <= n; j++) {
                if (j == i) continue;
                if (!taken && primes[j] == (tot ^ primes[i])) {
                    taken = true;
                    continue;
                }
                cout << j << ' ';
            }
            return;
        }
    }
    cout << n - 3 << '\n';
    for (int i = 1; i <= n; i++) {
        if (i == (n - 1)/2 || i == 2 || i == n) continue;
        cout << i << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    solve(n);

}
