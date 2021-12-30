#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int S, T, X;
    cin >> S >> T >> X;
    bool fine = true;
    for (int i = 1; i <= 24 + X; i++) {
        if ((i - 1) % 24 + 1 == S) {
            fine = true;
        } else if ((i - 1) % 24 + 1 == T) {
            fine = false;
        }
    }
    cout << (fine ? "Yes": "No");
}
