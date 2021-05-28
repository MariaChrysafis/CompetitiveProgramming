#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
vector<vector<int>> new_dp;
vector<vector<int>> old_dp;
vector<vector<int>> identity;
int to_int(char c){
    return c - '0';
}
int main(){
    string K;
    cin >> K;
    int D;
    cin >> D;
    new_dp.resize(D), old_dp.resize(D);
    for(int i = 0; i < D; i++){
        new_dp[i].resize(2), old_dp[i].resize(2);
        for(int j = 0; j < 2; j++){
            new_dp[i][j] = old_dp[i][j] = 0;
        }
    }
    identity = new_dp;
    //return 0;
    old_dp[0][0] = 1;
    for(char c: K){
        new_dp = identity;
        int x = to_int(c);
        for(bool b: {0,1}){
            for(int digits = 0; digits < 10; digits++){
                for(int sum = 0; sum < D; sum++){
                    if(!b && digits > x) continue;
                    new_dp[(digits + sum) % D][b || (digits < x)] += old_dp[sum][b];
                    new_dp[(digits + sum) % D][b || (digits < x)] %= MOD;
                }
            }
        }
        old_dp = new_dp;
    }
    cout << (old_dp[0][0] + old_dp[0][1] - 1 + MOD) % MOD << endl;
}
