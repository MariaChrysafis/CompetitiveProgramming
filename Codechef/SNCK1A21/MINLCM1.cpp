#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <climits>
#include <vector>
#include <set>

#define ll int

using namespace std;
long long gcd (long long a, long long b) {
    if (min(a,b) == 0) {
        return max(a,b);
    }
    return gcd(max(a,b) % min(a,b), min(a,b));
}
long long lcm(long long a, long long b) {
    return (a * b)/gcd(a,b);
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        long long a, b;
        cin >> a >> b;
        cout << 2 * a << " " << lcm(b * a, b * a - 1) << '\n';
    }
}
