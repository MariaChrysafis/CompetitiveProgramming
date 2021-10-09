#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O2")
using namespace std;

const int MOD = 1e9 + 7;

map <int,int> myMap;

int main() {
    myMap['A'] = 1, myMap['C'] = 2, myMap['T'] = 3, myMap['G'] = 0;
    string s;
    cin >> s;
    int n = s.length();
    long long dp[n][4][4][4];
    for (int i = 0; i < n; i++) {
        for (int a = 0; a < 4; a++) {
            for (int b = 0; b < 4; b++) {
                for (int c = 0; c < 4; c++) {
                    dp[i][a][b][c] = 0;
                }
            }
        }
    }
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (s[0] == '?' || myMap[s[0]] == a) {
                dp[0][b][a][a] = 1;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        for (int c1 = 0; c1 < 4; c1++) {
            for (int c2 = 0; c2 < 4; c2++) {
                for (int c3 = 0; c3 < 4; c3++) {
                    dp[i][c1][c2][c3] = 0;
                    if(myMap[s[i]] != c3 && s[i] != '?') {
                        continue;
                    }
                    for (int prev = 0; prev < 4; prev++) {
                        if (prev != c3) {
                            dp[i][c1][c2][c3] += dp[i - 1][c1][c2][prev];
                            dp[i][c1][c2][c3] %= MOD;
                        }
                    }
                }
            }
        }
        for (int c1 = 0; c1 < 4; c1++) {
            for (int c2 = 0; c2 < 4; c2++) {
                for (int c3 = 0; c3 < 4; c3++) {
                    if(myMap[s[i]] != c3 && s[i] != '?') {
                        continue;
                    }
                    for (int prev = 0; prev < 4; prev++) {
                        if(c1 == prev) {
                            dp[i][c2][c3][c3] += dp[i - 1][c1][c2][prev];
                            dp[i][c1][c2][c3] %= MOD;
                        }
                    }
                }
            }
        }
    }
    long long sum = 0;
    for (int c1 = 0; c1 < 4; c1++) {
        for (int c2 = 0; c2 < 4; c2++) {
            sum += dp[n - 1][c1][c2][c1];
            sum %= MOD;
        }
    }
    cout << sum << endl;
}
