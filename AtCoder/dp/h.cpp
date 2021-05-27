#include <iostream>
#include <vector>
using namespace std;
long long MOD = 1e9 + 7;
vector<vector<bool>> grid; /* 0 -> blocked, 1 -> valid */
vector<vector<long long>> dp;
long long H, W;
bool inBounds(long long h, long long w){
    return (h < H && w < W && h >= 0 && w >= 0);
}
long long best(long long h, long long w){
    if(!inBounds(h, w) || !grid[h][w]){
        return {0};
    }
    if(dp[h][w] != -1){
        return dp[h][w];
    }
    dp[h][w] = (best(h - 1, w) + best(h, w - 1)) % MOD;
    return dp[h][w];
}
int main(){
    cin >> H >> W;
    grid.resize(H);
    dp.resize(H);
    for(int i = 0; i < H; i++){
        grid[i].resize(W), dp[i].resize(W);
        for(int j = 0; j < W; j++){
            char c;
            cin >> c;
            grid[i][j] = (c == '.');
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 1;
    cout << best(H - 1, W - 1) << endl;
}
