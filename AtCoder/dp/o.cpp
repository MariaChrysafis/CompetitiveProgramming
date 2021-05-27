#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
vector<vector<long long>> dp; //first i men, some subset of the women
vector<vector<short int>> arr;
int n;
bool bitSet(int val, int bitNum){
    return (val >> bitNum) & 1;
}
long long memoize(int x, int y){
    if(x < 0){
        return 1;
    }
    if(dp[x][y] != -1){
        return dp[x][y];
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        if(bitSet(y,i) && arr[x][i]){
            ans += memoize(x - 1, y - (1 << i));
        }
    }
    dp[x][y] = ans % MOD;
    return dp[x][y];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    dp.resize(n);
    for(int i = 0; i < n; i++){
        dp[i].resize((int)pow(2,n + 1));
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = -1;
        }
    }
    arr.resize(n);
    for(int i = 0; i < n; i++){
        arr[i].resize(n);
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
    cout << memoize(n - 1, pow(2, n + 1) - 1);
}
