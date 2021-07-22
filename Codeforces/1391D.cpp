#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;
void print(vector<vector<int>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
const int INF = 1e9;
bool validTransition(int x, int y, int n){
    int a = ((x & 4) / 4 + (y & 4) / 4 + (x & 2) / 2 + (y & 2) / 2);
    int b = ((x & 1) + (y & 1) + (x & 2) / 2 + (y & 2) / 2);
    if(n == 3) {
        //cout << a << " " << b % 2 << endl;
        return ((a % 2 == 1) && (b % 2 == 1));
    }
    if(n == 2){
        return (b % 2 == 1);
    }
    if(n == 1){
        return true;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    if(n > 3){
        cout << "-1\n";
        return 0;
    }
    vector<vector<int>> arr(n);
    for(int i = 0; i < n; i++){
        arr[i].resize(m);
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            arr[i][j] = (s[j] == '1');
        }
    }
    vector<vector<int>> dp(m + 1);
    for(int i = 0; i <= m; i++){
        dp[i].resize(8);
    }
    for(int i = 0; i < 8; i++){
        dp[0][i] = INF;
    }
    for(int i = 0; i < (1 << n); i++){
        dp[0][i] = 0;
    }
    for(int i = 1; i <= m; i++){
        dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = dp[i][4] = dp[i][5] = dp[i][6] = dp[i][7] = INF;
    }
    for(int i = 1; i <= m; i++){
        for(int j = 0; j < (1 << n); j++){
            for(int k = 0; k < (1 << n); k++){
                if(!validTransition(j, k, n)){
                    continue;
                }
                int dif = 0;
                dif += (arr[0][i - 1] != (k & 1));
                if(n > 1) dif += (arr[1][i - 1] != (k & 2)/2);
                if(n > 2) dif += (arr[2][i - 1] != (k & 4)/4);
                dp[i][k] = min(dif + dp[i - 1][j], dp[i][k]);
            }
        }
    }
    int myMin = INF;
    for(int i = 0; i < 8; i++){
        myMin = min(myMin, dp[m][i]);
    }
    cout << myMin << endl;
}
