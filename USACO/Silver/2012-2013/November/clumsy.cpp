#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

using namespace std;
int main() {
    freopen("clumsy.in", "r", stdin);
    freopen("clumsy.out", "w", stdout);
    string s;
    cin >> s;
    int depth = 0;
    int cntr = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            depth++;
        } else {
            depth--;
        }
        if (depth < 0) {
            s[i] = '(';
            cntr++;
            depth += 2;
        }
    }
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            ans ++;
        } else {
            ans--;
        }
    }
    cout << cntr + abs(ans)/2 << endl;
}
