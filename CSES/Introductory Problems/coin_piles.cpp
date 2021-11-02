#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <iomanip>
#define ll unsigned long long
using namespace std;
int dist (pair<int,int> p1, pair<int,int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        ll a, b;
        cin >> a >> b;
        if ((a + b) % 3 != 0 ) {
            cout << "NO\n";
        } else if ((4 * a - 2 * b) % 3 != 0 || (4 * a - 2 * b) < 0) {
            cout << "NO\n";
        } else if ((4 * b - 2 * a) % 3 != 0 || (4 * b - 2 * a) < 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}
