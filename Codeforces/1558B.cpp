#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#define ll long long
using namespace std;
ll MOD, n;
map<int,int> create(int x){
    map<int,int> myMap;
    set<int> s;
    for(int i = 2; i <= x; i++){
        myMap[x/i]++;
    }
    return myMap;
}
vector<vector<pair<int,int>>> adj;
int main(){
    cin >> n >> MOD;
    long long dp[n + 1];
    for(int i = 0; i <= n; i++) dp[i] = 0;
    dp[1] = 1;
    dp[2] = -1;
    for(int i = 2; i <= n; i++){
        dp[i] += 2 * dp[i - 1] + 1;
        dp[i] %= MOD;
        for(int j = 2 * i; j <= n; j += i){
            dp[j] += (dp[i] - dp[i - 1] + MOD) % MOD;
            dp[j] %= MOD;
        }
    }
    cout << dp[n] << endl;
 
}
