#include <iostream>
#include <vector>
using namespace std;
const long long INF = 1e12 + 7;
int N;
vector<long long> arr;
vector<vector<long long>> dp;
long long ans(int l, int r, bool start){
    int mult;
    if(start) mult = 1;
    else mult = -1;
    if(dp[l][r] != INF){
        return dp[l][r];
    }
    if(r - l == 0){
        dp[l][r] = mult * arr[l];
        return dp[l][r];
    }
    long long case1 = ans(l + 1, r, !start) + mult * arr[l];
    long long case2 = ans(l, r - 1, !start) + mult * arr[r];
    if(start){
        dp[l][r] = max(case1, case2);
    }else{
        dp[l][r] = min(case1, case2);
    }
    return dp[l][r];
}
int main(){
    cin >> N;
    arr.resize(N);
    dp.resize(N);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
        dp[i].resize(N);
        for(int j = 0; j < N; j++){
            dp[i][j] = INF;
        }
    }
    cout << ans(0, N - 1, 1) << endl;
    //cout << dp[0][0] << " " << dp[1][1] << " " << dp[0][1] << endl;
}
