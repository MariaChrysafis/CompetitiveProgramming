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
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;

const int MAX = 1e6 + 1;

void solve (string s) {
    for (int i = s.length() - 2; i >= 0; i--) {
        char c1 = s[i];
        char c2 = s[i + 1];
        if ((c1 - '0') + (c2 - '0') >= 10) {
            string str = to_string(c1 - '0' + c2 - '0');
            s[i] = str[0];
            s[i + 1] = str[1];
            cout << s << '\n';
            return;
        }
    }
    reverse(s.begin(), s.end());
    char c1 = s[s.length() - 2];
    char c2 = s[s.length() - 1];
    s.pop_back();
    s.pop_back();
    s.push_back(to_string(c1 - '0' + c2 - '0').back());
    reverse(s.begin(), s.end());
    cout << s << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string s;
        cin >> s;
        solve(s);
    }
}
