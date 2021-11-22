#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <map>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    long long myMax = 0;
    for (int x = 0; x <= min(a, d); x++) {
        //x is how many ties we have
        long long y = min(d - x, min(c, b));
        myMax = max(myMax, x * e + y * f);
    }
    cout << myMax;
}
