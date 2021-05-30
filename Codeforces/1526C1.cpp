#include <iostream>
#include <vector>
#include <set>
using namespace std;
int n;
vector<vector<long long>> dp;
vector<long long> arr;
long long MAX = 1000;
long long memoize(long long cur, long long potions_drank){
    if(potions_drank > cur + 1) return -MAX;
    if(cur < 0 || potions_drank < 0) return 0;
    if(dp[cur][potions_drank] != -MAX){
        return dp[cur][potions_drank];
    }
    long long op1 = memoize(cur - 1,potions_drank - 1) + arr[cur];
    long long op2 = memoize(cur - 1, potions_drank);
    if(memoize(cur - 1,potions_drank - 1) < 0 || op1 < 0) op1 = -MAX;
    if(op2 < 0) op2 = -MAX;
    dp[cur][potions_drank] = max(op1, op2);
    return dp[cur][potions_drank];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    dp.resize(n);
    arr.resize(n);
    for(int i = 0; i < n; i++) dp[i].resize(n + 1);
    for(int i = 0; i < n; i++) cin >> arr[i];
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            dp[i][j] = -MAX;
        }
    }
    vector<int> ans;
    dp[0][0] = 0;
    dp[0][1] = arr[0];
    for(int j = 2; j <= n; j++){
        dp[0][j] = -MAX;
    }
    for(int i = 1; i < n; i++){
        for(int j = 0; j <= n; j++){
            long long op1;
            if(j == 0 || dp[i - 1][j - 1] < 0 || dp[i - 1][j - 1] + arr[i] < 0) op1 = -MAX;
            else op1 = dp[i - 1][j - 1] + arr[i];
            long long op2;
            if(dp[i - 1][j] < 0) op2 = -MAX;
            else op2 = dp[i - 1][j];
            dp[i][j] = max(op1, op2);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            //cout << dp[i][j] << " ";
            if(dp[n - 1][j] >= 0){
                ans.push_back(j);
            }
        }
        //cout << endl;
    }
    //cout << dp[1][0] << endl;
    cout << ans.back() << endl;
}
