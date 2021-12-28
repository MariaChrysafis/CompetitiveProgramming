#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <set>
#include <algorithm>
#include <random>
using namespace std;

int arr[(int)1e5];
int rev[(int)1e5];
int comp[(int)1e5];
int delta;

void recomp (int cur) {
    int orig = cur;
    for (int i = 0; i < delta; i++) {
        cur = rev[cur];
    }
    comp[cur] = orig;
    for (int i = 0; i < delta; i++) {
        cur = arr[cur];
        comp[cur] = arr[orig];
        orig = arr[orig];
    }
}

void solve(int n) {
    int Q;
    cin >> Q;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
        rev[arr[i]] = i;
    }
    delta = sqrt(n);
    for (int i = 0; i < n; i++) {
        int cur = i;
        for (int j = 0; j < delta; j++) {
            cur = arr[cur];
        }
        comp[i] = cur;
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            //swapping
            int x, y;
            cin >> x >> y;
            x--, y--;
            swap(arr[x], arr[y]);
            swap(rev[arr[x]], rev[arr[y]]);
            recomp(x), recomp(y);
        } else {
            //printing
            int cur, k;
            cin >> cur >> k;
            cur--;
            while (k >= delta) {
                k -= delta;
                cur = comp[cur];
            }
            while (k--) {
                cur = arr[cur];
            }
            cout << cur + 1 << '\n';
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    solve(n);

}
