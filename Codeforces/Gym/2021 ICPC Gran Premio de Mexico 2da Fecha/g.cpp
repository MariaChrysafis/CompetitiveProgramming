#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

void solve () {
    int n, m;
    cin >> n >> m;
    char arr[n][m];
    map<char,vector<pair<int,int>>> myMap;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            arr[i][j] = s[j];
            myMap[arr[i][j]].emplace_back(i, j);
        }
    }
    int dp[n][m];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            dp[i][j] = 1;
        }
    }
    for(char c = 'Z'; c >= 'A'; c--) {
        for(pair<int,int> p: myMap[c]) {
            for(int x = -1; x <= 1; x++) {
                for(int y = -1; y <= 1; y++) {
                    if(x + p.first == n || x + p.first < 0) continue;
                    if(y + p.second == m || y + p.second < 0) continue;
                    if(arr[p.first][p.second] + 1 == arr[x + p.first][y + p.second]) {
                        dp[p.first][p.second] = max(dp[p.first][p.second], dp[x + p.first][y + p.second] + 1);
                    }
                }
            }
        }
    }
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //cout << dp[i][j] << " ";
            myMax = max(myMax, dp[i][j]);
        }
        //cout << endl;
    }
    cout << myMax << endl;
}

int main() {
    solve();

}
