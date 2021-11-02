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
    int n;
    cin >> n;
    for (long long i = 1; i <= n; i++) {
        cout << (i - 1) * (i + 4) * (i * i - 3 * i + 4) / 2 << '\n';
    }
}
