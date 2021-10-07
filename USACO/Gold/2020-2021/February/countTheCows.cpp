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

#pragma GCC optimize("O3")
const int MAX = 40;
using namespace std;
vector<long long> powr;
void query(long long x, long long y, long long d) {
    // we're considering the first ___ digits
    // we have a carry of ___ on x
    // we have a carry of ____ on y
    // 0 -> digit must be less than that of k; 1 --> digit equal to that of k; 2 --> digit greater than that of k
    long long dp[MAX + 1][3][3][3];
    for (int i = 0; i <= MAX; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    dp[i][j][k][l] = 0;
                }
            }
        }
    }
    dp[0][0][0][1] = 1;
    for (int i = 0; i <= MAX - 1; i++) {
        long long cur_x = x/powr[i] % 3;
        long long cur_y = y/powr[i] % 3;
        long long cur_d = d/powr[i] % 3;
        for (int carry_x = 0; carry_x < 3; carry_x++) {
            for (int carry_y = 0; carry_y < 3; carry_y++) {
                for (int comp = 0; comp < 3; comp++) {
                    for (int place = 0; place < 3; place++)  {
                        int new_carry_x = (carry_x + place + cur_x) / 3 % 3;
                        int new_x = (carry_x + place + cur_x) % 3;
                        int new_carry_y = (carry_y + place + cur_y) / 3 % 3;
                        int new_y = (carry_y + place + cur_y) % 3;
                        int new_comp = comp;
                        if (place > cur_d) new_comp = 2;
                        else if (place < cur_d) new_comp = 0;
                        if(new_x % 2 == new_y % 2) {
                            dp[i + 1][new_carry_x][new_carry_y][new_comp] += dp[i][carry_x][carry_y][comp];
                        }
                    }
                }
            }
        }
    }
    cout << dp[MAX - 1][0][0][0] + dp[MAX - 1][0][0][1] << endl;
}
int main() {
    powr.push_back(1);
    while(powr.size() != MAX) {
        powr.push_back(3 * powr.back());
    }
    int q;
    cin >> q;
    while (q--) {
        long long x, y, d;
        cin >> d >> x >> y;
        query(x, y, d);
    }
}
