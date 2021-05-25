#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> h;
vector<int> dp;
const int INF = 1e9;
int memoize(int i){
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
    //cout << i << endl;
    dp[i] = min(memoize(i - 2) + abs(h[i - 2] - h[i]), memoize(i - 1) + abs(h[i - 1] - h[i]));
    return dp[i];
}
int main(){
    cin >> n;
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
