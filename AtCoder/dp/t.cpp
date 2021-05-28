#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
vector<vector<long long>> pref;
long long prefix(int x, int y){
    if(y < 0) return 0;
    else return pref[x][y];
}
int main(){
    int N;
    string s;
    cin >> N >> s;
    vector<vector<long long>> dp;
    vector<long long> sum;
    dp.resize(N + 1), pref.resize(N + 1), sum.resize(N + 1);
    for(int i = 0; i <= N; i++){
        dp[i].resize(N + 1), pref[i].resize(N + 1);
        sum[i] = 0;
        for(int j = 0; j <= N; j++){
            dp[i][j] = pref[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    pref[0][0] = 1;
    sum[0] = 1;
    for(int i = 1; i < N; i++){
        for(int j = 0; j <= i; j++){
            if(s[i - 1] == '<') dp[i][j] = prefix(i - 1, j - 1) % MOD;
            else dp[i][j] = (sum[i - 1] - prefix(i - 1, j - 1) + MOD) % MOD;
            sum[i] += dp[i][j];
            pref[i][j] = prefix(i, j - 1) + dp[i][j];
            sum[i] %= MOD, pref[i][j] %= MOD;
        }
    }
    cout << sum[N - 1] << endl;
}
