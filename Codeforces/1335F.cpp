#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
pair<int,int> nxt(int i, int j, char c){
    if(c == 'D') return {i + 1, j};
    if(c == 'U') return {i - 1, j};
    if(c == 'R') return {i, j + 1};
    return {i, j - 1};
}
void solve(){
    int n, m;
    cin >> n >> m;
    char dir[n][m];
    bool col[n][m];
    for(int i = 0; i < n; i++){
        string s; cin >> s;
        for(int j = 0; j < m; j++){
            col[i][j] = (s[j] == '1');
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> dir[i][j];
        }
    }
    pair<int,int> dp[n][m][21];
    for(int jump = 0; jump < 21; jump++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (jump == 0) {
                    dp[i][j][0] = nxt(i, j, dir[i][j]);
                } else {
                    dp[i][j][jump] = dp[dp[i][j][jump - 1].first][dp[i][j][jump - 1].second][jump - 1];
                }
            }
        }
    }
    map<pair<int,int>,vector<pair<int,int>>> myMap;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            myMap[{dp[i][j][20].first, dp[i][j][20].second}].push_back({i, j});
        }
    }
    int a1 = 0;
    int a2 = 0;
    for(auto q: myMap){
        pair<int,int> ind = q.first;
        bool black = false;
        for(auto p: myMap[ind]){
            if(!col[p.first][p.second]){
                black = true;
                break;
            }
        }
        a2 += black;
        a1++;
    }
    cout << a1 << " " << a2 << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
 
}
