#include <iostream>
#include <vector>
using namespace std;
int n;
int k;
vector<int> h;
vector<int> dp;
const int INF = 1e9;
int memoize(int i){
    if(i < 0){
        return INF;
    }
    if(i == 0){
        dp[i] = 0;
        return 0;
    }
    if(i == 1){
        dp[i] = abs(h[1] - h[0]);
        return dp[i];
    }
    if(dp[i] != INF){
        return dp[i];
    }
    for(int j = 1; j <= k; j++){
        dp[i] = min(memoize(i - j) + abs(h[i] - h[i - j]), dp[i]);
    }
    return dp[i];
}
int main(){
    cin >> n;
    cin >> k;
    h.resize(n);
    dp.resize(n);
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        h[i] = a;
        dp[i] = INF;
    }
    int ans = memoize(n - 1);
    //for(int i: dp) cout << i << " ";
    cout << ans << endl;
}
