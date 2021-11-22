#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <map>
using namespace std;
char flip (char c) {
    if (c == 'W') return 'B';
    else return 'W';
}
void solve (string s, char c) {
    vector<int> indices;
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] != c) {
            s[i] = flip(s[i]);
            s[i + 1] = flip(s[i + 1]);
            indices.push_back(i);
        }
    }
    cout << indices.size() << '\n';
    for (int i: indices) {
        cout << i + 1 << " ";
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int w = 0; int b = 0;
    for (int i = 0; i < s.length(); i++) {
        w += (s[i] == 'W');
        b += (s[i] == 'B');
    }
    if (w % 2 != n % 2 && b % 2 != n % 2) {
        cout << "-1\n";
        return 0;
    }
    if (w % 2 == n % 2) {
        solve(s, 'W');
    } else {
        solve(s, 'B');
    }
}
