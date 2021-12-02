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
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 = abs(x1), y1 = abs(y1), x2 = abs(x2), y2 = abs(y2);
        cout << 2 * (x1 % 2) + y1 % 2 + 1 << '\n';
    }
}
