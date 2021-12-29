#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

void solve() {
    int x;
    cin >> x;
    if (x >= 42) {
        x++;
    }
    string s = to_string(x);
    while (s.length() != 3) {
        s = "0" + s;
    }
    cout << "AGC" << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
