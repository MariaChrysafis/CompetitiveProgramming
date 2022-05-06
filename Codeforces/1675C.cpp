#include <bits/stdc++.h>
using namespace std;
int solve (string s) {
    int cntr = 0;
    for (int i = 0; i < s.length(); i++)  {
        cntr += (s[i] == '1');
    }
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        cntr -= (s[i] == '1');
        cntr += (s[i] == '0');
        ans += (cntr == 0 || (cntr == 1 && s[i] == '0'));
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << solve(s) << '\n';
    }
}
