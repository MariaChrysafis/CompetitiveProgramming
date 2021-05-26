#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const long long INF = 1e12;
int n, w;
vector<vector<long long>> dp;
vector<long long> weight, value;
int main(){
    cin >> n >> w;
    dp.resize(n), weight.resize(n), value.resize(n);
    long long sm = 0;
    for(int i = 0; i < n; i++){
        cin >> weight[i] >> value[i];
        sm += value[i];
        dp[i].resize(sm + 1);
    }
    for(int i = 0; i < dp.size(); i++){
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0; dp[0][value[0]] = weight[0];
    for(int i = 1; i < dp.size(); i++){
        for(int j = 0; j < dp[i].size(); j++){
            if(j - value[i] >= 0) dp[i][j] = dp[i - 1][j - value[i]] + weight[i];
            if(dp[i - 1].size() > j) dp[i][j] = min(dp[i][j], dp[i - 1][j]);
        }
    }
    for (int i = dp[n - 1].size() - 1; i >= 0; i--) {
        if(dp[n - 1][i] <= w){
            cout << i << endl;
            return 0;
        }
    }
}
