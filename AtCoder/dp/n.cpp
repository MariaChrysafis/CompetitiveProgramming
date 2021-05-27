#include <iostream>
#include <vector>
using namespace std;
vector<long long> arr;
vector<long long> pref;
vector<vector<long long>> dp;
int N;
long long sum(int l, int r){
    if(l == 0) return pref[r];
    return pref[r] - pref[l - 1];
}
long long memoize(int l, int r){
    if(r - l == 0){
        return 0;
    }
    if(dp[l][r] != -1){
        return dp[l][r];
    }
    long long ans = 1e15;
    for(int i = l; i < r; i++){
        long long op3 = memoize(l, i) + memoize(i + 1, r) + sum(l, r);
        ans = min(ans, op3);
    }
    dp[l][r] = ans;
    return ans;
}
int main(){
    cin >> N;
    arr.resize(N);
    pref.resize(N);
    dp.resize(N);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
        dp[i].resize(N);
        for(int j = 0; j < N; j++){
            dp[i][j] = -1;
        }
    }
    pref[0] = arr[0];
    for(int i = 1; i < N; i++) pref[i] = pref[i - 1] + arr[i];
    cout << memoize(0, N - 1) << endl;
}
