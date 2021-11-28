#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    int cntr = 0;
    for (int i = 0; i < (int)s.length() - 2; i++) {
        if (s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c') {
            cntr++;
        }
    }
    while (q--) {
        int x;
        char c;
        cin >> x >> c;
        x--;
        if (s[x] == c) {
            cout << cntr << '\n';
            continue;
        }
        if (x - 1 >= 0 && x + 1 < s.length() && s[x - 1] == 'a' && s[x] == 'b' && s[x + 1] == 'c') {
            cntr--;
        }
        if (x - 2 >= 0 && s[x - 2] == 'a' && s[x - 1] == 'b' && s[x] == 'c') {
            cntr--;
        }
        if (x + 2 < s.length() && s[x] == 'a' && s[x + 1] == 'b' && s[x + 2] == 'c') {
            cntr--;
        }
        s[x] = c;
        if (x - 1 >= 0 && x + 1 < s.length() && s[x - 1] == 'a' && s[x] == 'b' && s[x + 1] == 'c') {
            cntr++;
        }
        if (x - 2 >= 0 && s[x - 2] == 'a' && s[x - 1] == 'b' && s[x] == 'c') {
            cntr++;
        }
        if (x + 2 < s.length() && s[x] == 'a' && s[x + 1] == 'b' && s[x + 2] == 'c') {
            cntr++;
        }
        cout << cntr << '\n';
    }
}
