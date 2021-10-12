#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>

#define ll long long

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    bool available[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            available[i][j] = true;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int b = 0; b <= 1; b++) {
                int len = 1;
                while (true) {
                    int x = i + (len + !b) / 2;
                    int y = j + (len + b) / 2;
                    if (x >= n || y >= m) {
                        break;
                    }
                    len++;
                }
                ans += len - 1;
            }
        }
    }
    ans += n * m;
    //cout << ans << endl;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        vector<int> vec1;
        int new_ans1 = 1;
        for (int b: vector<int>({0, 1})) {
            int len = 1;
            while (true) {
                int x1 = x + (len + !b) / 2;
                int y1 = y + (len + b) / 2;
                if (x1 >= n || y1 >= m || !available[x1][y1]) {
                    break;
                }
                len++;
            }
            new_ans1 += len;
            vec1.push_back(len);
        }
        vector<int> vec2;
        int new_ans2 = 1;
        for (int b = 0; b <= 1; b++) {
            int len = 1;
            while (true) {
                int x1 = x - (len + !b) / 2;
                int y1 = y - (len + b) / 2;
                if (x1 < 0 || y1 < 0 || !available[x1][y1]) {
                    break;
                }
                len++;
            }
            new_ans2 += len;
            vec2.push_back(len );
        }
        int d = vec1[0] * vec2[1] + vec1[1] * vec2[0] - 1;
        //d = vec1[1] * vec2[1] + vec1[0] * vec2[0];
        //cout << vec1[0] << " " << vec1[1] << " " << vec2[0] << " " << vec2[1] << endl;
        if (available[x][y]) {
            ans -= d;
        } else {
            ans += d;
        }
        available[x][y] = !available[x][y];
        cout << ans << endl;
    }
}
