#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

long long solver (long long C, long long R, long long S) {
    if((R + C) % S == 0) {
        return C/S;
    }
    if (C < (R + C) % S) {
        return 0;
    }
    if (C >= (R + C) % S) {
        return solver(C - (R + C) % S, R, S) + 1;
    }

}

void solve () {
    long long C, R, S;
    cin >> C >> R >> S;
    cout << solver(C, R, S) << " ";
    long long moves = (C + R + S - 1)/S;
    cout << max(moves - R, 0ll) << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
