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

string s;
int K;

bool valid (int len) {
    if (len == 0) {
        return true;
    }
    int period = 0;
    for (int i = 0; i < len; i++) {
        period += (s[i] == '.');
    }
    if (period <= K) {
        return true;
    }
    for (int i = 1; i <= s.length() - len; i++) {
        //i...i + len - 1
        period -= (s[i - 1] == '.');
        period += (s[i + len - 1] == '.');
        if (period <= K) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s >> K;
    int l = 0;
    int r = s.length();
    while (l != r) {
        int m = (l + r + 1)/2;
        if (valid(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l;
}
