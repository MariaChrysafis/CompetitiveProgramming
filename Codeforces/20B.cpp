#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll A, B, C;
    cin >> A >> B >> C;
    double discriminant = B * B - 4 * A * C;
    if (discriminant < 0) {
        cout << "0\n";
        return 0;
    }
    discriminant = sqrt(discriminant);
    //cout << discriminant << '\n';
    if (A == 0) {
        if (B == 0 && C == 0) {
            cout << "-1\n";
            return 0;
        }
        if (B == 0) {
            cout << "0\n";
            return 0;
        }
        cout << 1 << '\n';
        cout << fixed << setprecision(30) << (-1.0 * C)/B;
        return 0;
    }
    double a1 = (-(double)B + (double)discriminant)/(2 * (double)A);
    double a2 = (-(double)B - (double)discriminant)/(2.0 * (double)A);
    if (a1 > a2) {
        swap(a1, a2);
    }
    if (discriminant == 0) {
        cout << fixed << setprecision(30) << "1\n" << a1 << '\n';
        return 0;
    }
    cout << fixed << setprecision(30) << "2\n" << a1 << '\n' << a2 << '\n';
}
