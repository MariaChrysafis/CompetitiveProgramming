#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <map>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int,int>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    double myMax = 0;
    for (auto& p: vec) {
        for (auto& q: vec) {
            double x = abs(p.first - q.first);
            double y = abs(p.second - q.second);
            myMax = max(myMax, sqrt(x * x + y * y));
        }
    }
    cout << setprecision(30) << myMax;
}
