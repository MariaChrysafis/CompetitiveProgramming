#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const long long INF = 1e12;
int n, w;
vector<vector<long long>> dp;
vector<long long> weight, value;
long long memoize(int x, int y){
    if(x < 0 || y < 0) {
        if(y != 0) return -INF;
        else return 0;
    }
    if(dp[x][y] != -INF){
        return dp[x][y];
    }
    if(y == 0){
        dp[x][y] = 0;
        return dp[x][y];
    }
    dp[x][y] = max(memoize(x - 1, y - weight[x]) + value[x], memoize(x - 1, y));
    return dp[x][y];
}
int main(){
    cin >> n >> w;
    dp.resize(n), weight.resize(n), value.resize(n);
    for(int i = 0; i < n; i++){
        dp[i].resize(w + 1);
        for(int j = 0; j <= w; j++){
            dp[i][j] = -INF;
        }
        cin >> weight[i] >> value[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= w; j++){
            dp[i][j] = memoize(i, j);
        }
    }
    long long myMax = 0;
    for (int i = w; i >= 0; i--) {
        myMax = max(dp[n - 1][i], myMax);
    }
    cout << myMax << endl;
}
