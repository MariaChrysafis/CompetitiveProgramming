#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
using namespace std;
vector<int> v;

int oc[(int)5e5 + 1];
void Swap (int i, int j) {
    swap(v[i], v[j]);
    oc[v[i]] = i; oc[v[j]] = j;
}
void cycle (int i, int j, int k) {
    if (i == j || j == k || i == k) return;
    Swap (i, j);
    Swap (j, k);
}
bool solve() {
    int n;
    cin >> n;
    v.resize(n);
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        s.insert(v[i]);
        oc[v[i]] = i;
    }
    if (s.size() != n) {
        return true;
    }
    vector<int> sorted = v;
    sort(sorted.begin(), sorted.end());
    bool fine = true;
    for (int i = 0; i < n; i++) {
        if (sorted[i] != v[i]) {
            int j = oc[sorted[i]];
            if (j > i) {
                if (j + 1 < n) {
                    cycle(i, j, j + 1);
                } else if (j - 1 != i) {
                    cycle(i, j, j - 1);
                }
            }
        }
        if (sorted[i] != v[i]) {
            fine = false;
            break;
        }
    }
    if (fine) {
        return true;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        bool b = solve();
        cout << (b ? "YES" : "NO") << '\n';
    }


}
