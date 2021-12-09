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
#pragma GCC optimization ("unroll-loops")

#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    set<int> pos;
    vector<int> v(m);
    for (int i = 0; i < n; i++) {
        int x; cin >> x; x %= m;
        v[x]++;
    }
    if (n > m) {
        cout << "YES\n";
        return 0;
    }
    for (int i = 0; i < m; i++) {
        vector<int> add;
        for (int x = 1; x <= v[i]; x++) {
            add.push_back((i * x) % m);
            for (int j: pos) {
                add.push_back((i * x + j) % m);
            }
        }
        for (int j: add) {
            pos.insert(j);
            if (j == 0) {
                break;
            }
        }
    }
    if (pos.count(0)) {
        cout << "YES";
    } else {
        cout << "NO";
    }


}
