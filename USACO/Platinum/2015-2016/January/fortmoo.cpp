#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int N, M;
vector<vector<int>> arr;
vector<vector<int>> dp; /* dp[i][j] gives the number of 'X's in the square with
                           coordinates (i,j) and (0,0) */
int sm(int x, int y) {
    if (dp[x][y] != -1) {
        return dp[x][y];
    }
    if (x == 0 && y == 0) {
        dp[0][0] = arr[0][0];
        return dp[0][0];
    }
    if (x == 0) {
        dp[x][y] = sm(0, y - 1) + arr[0][y];
        return dp[x][y];
    }
    if (y == 0) {
        dp[x][y] = sm(x - 1, 0) + arr[x][0];
        return dp[x][y];
    }
    dp[x][y] = sm(x - 1, y) + sm(x, y - 1) - sm(x - 1, y - 1) + arr[x][y];
    return dp[x][y];
}
int rect(int x1, int y1, int x2, int y2) {
    if (y1 == 0 && x1 == 0) {
        return dp[x2][y2];
    }
    if (y1 == 0) {
        return dp[x2][y2] - dp[x1 - 1][y2];
    }
    if (x1 == 0) {
        return dp[x2][y2] - dp[x2][y1 - 1];
    }
    if (y1 == y2 && x1 == x2) {
        return arr[x1][y1];
    }
    int val = dp[x2][y1 - 1] + dp[x1 - 1][y2] - dp[x1 - 1][y1 - 1];
    return dp[x2][y2] - val;
}
int main() {
    ifstream in("fortmoo.in");
    ofstream out("fortmoo.out");
    in >> N >> M;
    dp.resize(N), arr.resize(N);
    for (int i = 0; i < N; i++) {
        dp[i].resize(M), arr[i].resize(M);
        for (int j = 0; j < M; j++) {
            dp[i][j] = -1;
            char c;
            in >> c;
            arr[i][j] = (c == 'X');
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dp[i][j] = sm(i, j);
        }
    }
    // out << rect(0, 0, 0, 0) << endl;
    // return 0;
    int fin = 0;
    for (int i = 0; i < M; i++) {
        for (int k = i; k < M; k++) {
            int ans = 0;
            int myMax = 0;
            for (int x = N - 1; x >= 0; x--) {
                if (ans == 0) {
                    ans = (rect(x, i, x, k) == 0);
                } else {
                    if(arr[x][i] || arr[x][k]){
                        ans = 0;
                        continue;
                    }
                    if (rect(x, i, x, k) > 0) {
                        ans++;
                        continue;
                    } else {
                        ans++;
                    }
                }
                //out << i << " " << k << " " << ans << endl;
                myMax = max(ans, myMax);
            }
            fin = max(myMax * (k - i + 1), fin);
            //out << myMax * (k - i + 1) << endl;
        }
    }
    out << fin << endl;
}
