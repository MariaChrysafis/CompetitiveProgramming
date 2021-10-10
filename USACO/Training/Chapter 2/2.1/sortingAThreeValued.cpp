/*
ID: maria.c2
TASK: sort3
LANG: C++14
*/
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O2")
using namespace std;

int main() {
    freopen("sort3.in", "r", stdin);
    freopen("sort3.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> sorted(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sorted = v;
    sort(sorted.begin(), sorted.end());
    int cntr = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] == sorted[i]) {
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if (sorted[i] == v[j] && sorted[j] == v[i]) {
                swap(v[i], v[j]);
                cntr ++;
                break;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (sorted[i] != v[i]) {
            ans++;
        }
    }
    if (ans == 0) cout << cntr << endl;
    else if (ans == 4) cout << cntr + (ans + 1)/2 << endl;
    else cout << cntr + (ans + 2)/2 << endl;
}
