#include <vector>
#include <iostream>
#include <cmath>
const long long MOD = 998244353;
using namespace std;
int main(){
    int n;
    cin >> n;
    pair<char,long long> arr[n];
    for(int i = 0; i < n; i++){
        char c;
        cin >> c;
        if(c == '-'){
            arr[i] = {'-', -1};
        }else{
            int x;
            cin >> x;
            arr[i] = {'+', x};
        }
    }
    long long dp[n + 1][n + 1];
    long long sum = 0;
    for(int x = 0; x < n; x++){
        if(arr[x].first == '-') continue;
        for(int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = 0;
            }
        }
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j <= n; j++){
                dp[i][j] = dp[i - 1][j];
                if(i - 1 == x){
                    continue;
                }
                if(arr[i - 1].first == '-'){
                    if(j + 1 <= n) dp[i][j] += dp[i - 1][j + 1];
                    if(j == 0 && i - 1 < x) dp[i][j] += dp[i - 1][0];
                }else{
                    bool b = ((arr[i - 1].second < arr[x].second) || arr[i - 1].second == arr[x].second && i - 1 < x);
                    if(b){
                        if(j != 0) dp[i][j] += dp[i - 1][j - 1];
                    }else{
                        dp[i][j] += dp[i - 1][j];
                    }
                }
                dp[i][j] %= MOD;
            }
        }
        for(int j = 0; j <= n; j++){
            sum += (dp[n][j] * arr[x].second) % MOD;
            sum %= MOD;
        }
    }
    cout << sum << endl;
}
