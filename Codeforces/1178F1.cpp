#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
void printsp(vector<int> v){
    for(int i: v) cout << 1 << " " << i + 1 << '\n';
    cout << endl;
}
void print(vector<int> v){
    cout << v.size() << " ";
    for(int i: v) cout << i + 1 << " ";
    cout << '\n';
}
vector<vector<int>> dp;
vector<int> ind, arr;
const int MOD = 998244353;
int mult(int a, int b){
    return ((long long)a * (long long) b) % MOD;
}
int memoize(int l, int r){
    if(l >= r){
        return 1;
    }
    if(dp[l][r] != -1){
        return dp[l][r];
    }
    int myMin = 1e9;
    for(int i = l; i <= r; i++){
        myMin = min(myMin, arr[i]);
    }
    int left = 0;
    for(int a = l; a <= ind[myMin]; a++){
        left += mult(memoize(l, a - 1), memoize(a, ind[myMin] - 1));
        left %= MOD;
    }
    int right = 0;
    for(int b = ind[myMin]; b <= r; b++){
        right += mult(memoize(ind[myMin] + 1, b), memoize(b + 1, r));
        right %= MOD;
    }
    return (dp[l][r] = mult(left, right));
}
void solve(){
    int n;
    cin >> n;
    int m;
    cin >> m;
    dp.resize(n + 1);
    ind.resize(n + 1), arr.resize(n);
    for(int i = 0; i < dp.size(); i++){
        dp[i].resize(dp.size());
        for(int j = 0; j < dp.size(); j++){
            dp[i][j] = -1;
        }
    }
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        ind[arr[i]] = i;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            memoize(i, j);
        }
    }
    cout << memoize(0, n - 1) << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
 
 
}
