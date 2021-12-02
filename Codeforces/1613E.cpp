#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <algorithm>
#pragma GCC optimize("Ofast")

#define ll int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int x1, p1, x2, p2;
        cin >> x1 >> p1 >> x2 >> p2;
        int mn = min(p1, p2);
        p1 -= mn;
        p2 -= mn;
        if (p1 - p2 >= 7) {
            cout << ">\n";
            continue;
        }
        if (p2 - p1 >= 7) {
            cout << "<\n";
            continue;
        }
        if (x1 * pow(10, p1) > x2 * pow(10, p2)) {
            cout << ">\n";
            continue;
        }
        if (x1 * pow(10, p1) < x2 * pow(10, p2)) {
            cout << "<\n";
            continue;
        }
        cout << "=\n";
    }
}
