#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
vector<vector<long long>> dp;
vector<long long> pref;
vector<long long> prefBackUp;
long long prefix(int y1, int y2){
    if(y1 >= 1){
        return prefBackUp[y2] - prefBackUp[y1 - 1];
    }
    if(y1 <= 0){
        return prefBackUp[y2];
    }
}
int main(){
    int N, K;
    cin >> N >> K;
    vector<long long> arr(N);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    dp.resize(N), pref.resize(K + 1), prefBackUp.resize(K + 1);
    for(int i = 0; i < N; i++) dp[i].resize(K + 1);
    pref[0] = dp[0][0] = 1;
    //return 0;
    for(int i = 1; i <= arr[0]; i++){
        pref[i] = pref[i - 1] + 1;
        dp[0][i] = 1;
    }
    for(int i = arr[0] + 1; i <= K; i++){
        pref[i] = pref[i - 1];
        dp[0][i] = 0;
    }
    prefBackUp = pref;
    for(int i = 1; i < N; i++){
        for(int j = 0; j <= K; j++){
            //dp[i][j] = \sum_{x = 0}^{a_i} dp[i - 1][j - x]
            dp[i][j] = (prefix(j - arr[i], j)) % MOD;
            if(j != 0) pref[j] = (dp[i][j] + pref[j - 1]) % MOD;
            else pref[j] = dp[i][j];
        }
        prefBackUp = pref;
    }
    cout << (dp[N - 1][K] + MOD) % MOD << endl;
}
