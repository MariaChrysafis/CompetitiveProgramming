#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

bool isPrime (int x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int Q;
    cin >> Q;
    while (Q--) {
        int x;
        cin >> x;
        //4 4 4 ... 4 if it's 0 (mod 4)
        //4 4 4 ... 9 if it's 1 (mod 4)
        //4 4 4 ... 6 if it's 2 (mod 4)
        //4 4 4 ... 10 if it's 3 (mod 4)
        if (x == 1 || x == 2 || x == 3 || x == 5  || x == 7 || x == 11) {
            cout << "-1\n";
            continue;
        }
        if (x % 2 == 0) {
            cout << x/4 << '\n';
            continue;
        }
        //otherwise it's odd
        cout << x/4 - 1 << '\n';
    }
}
