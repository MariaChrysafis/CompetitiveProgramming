#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <cmath>
#include <set>
using namespace std;
int cst (string s) {
    int a = 0;
    int b = 0;
    int m = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'A') {
            a++;
            b = 0;
        } else {
            b++;
            a = 0;
        }
        m = max(a, max(b, m));
    }
    return m;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        string s;
        cin >> s;
        if (k % 2 == 1) {
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '0') {
                    s[i] = '1';
                } else {
                    s[i] = '0';
                }
            }
        }
        vector<int> moves;
        moves.assign(n, 0);
        for (int i = 0; i < s.length(); i++) {
            if (k && s[i] == '0') {
                s[i] = '1';
                moves[i]++;
                k--;
            }
        }
        if (k % 2 == 1) {
            s.back() = '0';
        }
        while (k) {
            moves.back()++;
            k--;
        }
        cout << s << '\n';
        for (int i = 0; i < s.length(); i++) {
            cout << moves[i] << ' ';
        }
        cout << '\n';

    }
}
