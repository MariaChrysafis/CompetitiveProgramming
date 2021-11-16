/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Maria Chrysafis (Olympia)
 */



#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <random>

using namespace std;

class CGarland {
public:
    void solve(std::istream &in, std::ostream &out) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        int n;
        in >> n;
        vector<int> v(n);
        int cnt[2];
        cnt[0] = (n) / 2;
        cnt[1] = (n + 1) / 2;
        for (int i = 0; i < n; i++) {
            in >> v[i];
            if (v[i] != 0) {
                cnt[v[i] % 2]--;
                //cnt[v[i] % 2]--;
            }
        }
        int dp[n + 1][n + 1][n + 1][2]; //ind, even, odd
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= n; k++) {
                    dp[i][j][k][0] = -10000;
                    dp[i][j][k][1] = -10000;
                }
            }
        }
        dp[0][0][0][0] = 0;
        dp[0][0][0][1] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= n; k++) {
                    if (k != 0) {
                        dp[i][j][k][1] = max(dp[i - 1][j][k - 1][1] + 1, dp[i][j][k][1]);
                        dp[i][j][k][1] = max(dp[i - 1][j][k - 1][0], dp[i][j][k][1]);
                    }
                    if (j != 0) {
                        dp[i][j][k][0] = max(dp[i - 1][j - 1][k][0] + 1, dp[i][j][k][0]);
                        dp[i][j][k][0] = max(dp[i - 1][j - 1][k][1], dp[i][j][k][0]);
                    }
                    if (v[i - 1] != 0) {
                        if (v[i - 1] % 2 == 0) {
                            dp[i][j][k][1] = -100000;
                        } else {
                            dp[i][j][k][0] = -100000;
                        }
                    }
                }
            }
        }
        out << n - max(dp[n][n/2][(n + 1)/2][1], dp[n][n/2][(n + 1)/2][0]) << '\n';
    }
};


int main() {
	CGarland solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
