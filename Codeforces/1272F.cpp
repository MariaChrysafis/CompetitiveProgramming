#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <map>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
int val (char c) {
    if (c == '(') return 1;
    return -1;
}
string ts (char c) {
    string s;
    return (s += c);
}
const int MAX = 205;
struct Tuple {
    short int a;
    short int b;
    short int c;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s, t;
    cin >> s >> t;
    int dp[s.length() + 1][t.length() + 1][MAX];
    pair<int8_t,Tuple> prev[s.length() + 1][t.length() + 1][MAX];
    string myMap[4];
    myMap[0] = ")(";
    myMap[1] = ")";
    myMap[2] = "(";
    map<string,int> mm;
    for (int i = 0; i < 3; i++) {
        mm[myMap[i]] = i;
    }
    for (short int i = 0; i <= s.length(); i++) {
        for (short int j = 0; j <= t.length(); j++) {
            for (short int pref = 0; pref < MAX; pref++) {
                if (i == 0 && j == 0 && pref == 0) {
                    dp[i][j][pref] = 0;
                } else {
                    dp[i][j][pref] = 1e9;
                }
                /*
                 * case 0: we just insert a '(' at the end
                 */
                if (pref >= 1) {
                    int nxt = dp[i][j][pref - 1];
                    if (nxt + 1 < dp[i][j][pref ]) {
                        dp[i][j][pref] = nxt + 1;
                        prev[i][j][pref] = {2, {i, j, static_cast<short int>(pref - 1)}};
                    }
                }
                /*
                 * case 1: we just update t
                 */
                if (j != 0 && pref - val(t[j - 1]) < MAX) {
                    //cout << "YES\n";
                    if (pref - val(t[j - 1]) >= 0) {
                        int nxt = dp[i][j - 1][pref - (val(t[j - 1]))];
                        if (nxt + 1 < dp[i][j][pref]) {
                            dp[i][j][pref] = nxt + 1;
                            prev[i][j][pref] = {mm[ts(t[j - 1])], {i, static_cast<short int>(j - 1), static_cast<short int>(pref - val(t[j - 1]))}};
                        }
                    } else {
                        int nxt = dp[i][j - 1][pref];
                        if (nxt + 2 < dp[i][j][pref]) {
                            dp[i][j][pref] = nxt + 2;
                            prev[i][j][pref] = {mm[")("], {i, static_cast<short int> (j - 1), pref}};
                        }
                    }
                }
                /*
                 * case 2: we just update s
                 */
                if (i != 0 && pref - val(s[i - 1]) < MAX) {
                    if (pref - val(s[i - 1]) >= 0) {
                        int nxt = dp[i - 1][j][pref - val(s[i - 1])];
                        if (nxt + 1 < dp[i][j][pref]) {
                            dp[i][j][pref] = nxt + 1;
                            prev[i][j][pref] = {mm[ts(s[i - 1])], {static_cast<short int>(i - 1), j, static_cast<short int>(pref - val(s[i - 1]))}};
                        }
                    } else {
                        int nxt = dp[i - 1][j][pref];
                        if (nxt + 2 < dp[i][j][pref]) {
                            dp[i][j][pref] = nxt + 2;
                            prev[i][j][pref] = {mm[")("], {static_cast<short int>(i - 1), j, pref}};
                        }
                    }
                }
                /*
                 * case 3: we just update s and t
                 */
                if (i != 0 && j != 0 && s[i - 1] == t[j - 1] && pref - val(s[i - 1]) < MAX) {
                    if ( pref - val(s[i - 1]) >= 0) {
                        int nxt = dp[i - 1][j - 1][pref - val(s[i - 1])];
                        if (nxt + 1 < dp[i][j][pref]) {
                            dp[i][j][pref] = nxt + 1;
                            prev[i][j][pref] = {mm[ts(s[i - 1])], {static_cast<short int>(i - 1), static_cast<short int>(j - 1), static_cast<short int>(pref - val(s[i - 1]))}};
                        }
                    } else {
                        int nxt = dp[i - 1][j - 1][pref];
                        if (nxt + 2 < dp[i][j][pref]) {
                            dp[i][j][pref] = nxt + 2;
                            prev[i][j][pref] = {mm[")("], {static_cast<short int>(i - 1), static_cast<short int>(j - 1), pref}};
                        }
                    }
                }
            }
        }
    }
    int x = s.length();
    int y = t.length();
    int pref = 0;
    string myStr = "";
    while (! (x == 0 && y == 0 && pref == 0)) {
        pair<int,Tuple> ps = prev[x][y][pref];
        x = ps.second.a;
        y = ps.second.b;
        pref = ps.second.c;
        myStr += myMap[ps.first];
    }
    reverse(myStr.begin(), myStr.end());
    cout << myStr;
}
