#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
#include <map>
 
using namespace std;
 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
vector<bool> isPrime;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
vector<vector<int>> dp;
vector<int> nxt;
int memoize(int i, int j){
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    if(j == 0){
        return dp[i][j] = nxt[i];
    }
    dp[i][j] = memoize(memoize(i, j - 1), j - 1);
    return dp[i][j];
}
void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<vector<int>> myVec(isPrime.size());
    for(int i = 0; i < n; i++){
        int  x = v[i];
        if(isPrime[x]){
            myVec[x].push_back(i);
        }else{
            int y = x;
            for(int j = 2; j <= sqrt(x); j++){
                if(isPrime[j] && x % j == 0){
                    myVec[j].push_back(i);
                    while(y % j == 0){
                        y /= j;
                    }
                }
            }
            if(isPrime[y]){
                myVec[y].push_back(i);
            }
        }
    }
    vector<int> arrows(n);
    for(int i = 0; i < n; i++){
        arrows[i] = 1e9;
    }
    for(int i = 0; i < 1e5 + 7; i++){
        if(myVec[i].size() <= 1) continue;
        for(int j = 0; j < myVec[i].size() - 1; j++){
            arrows[myVec[i][j]] = min(arrows[myVec[i][j]], myVec[i][j + 1]);
        }
    }
    nxt.resize(n + 1);
    nxt[n] = n;
    for(int i = n - 1; i >= 0; i--){
        nxt[i] = min(nxt[i + 1], arrows[i]);
    }
    dp.resize(n + 1);
    for(int i = 0; i <= n; i++){
        dp[i].resize((int)log2(n) + 3);
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = -1;
        }
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = memoize(i, j);
        }
    }
    while(q--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        int ans = 0;
        for(int i = dp[0].size() - 1; i >= 0; i--){
            if(dp[l][i] <= r){
                ans += (1 << i);
                l = dp[l][i];
            }
        }
        cout << ans + 1 << endl;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    isPrime.resize(1e5 + 10);
    for(int i = 0; i < isPrime.size(); i++){
        isPrime[i] = true;
    }
    isPrime[1] = false, isPrime[0] = false;
    for(int i = 2; i < isPrime.size(); i++){
        if(isPrime[i]) {
            for (int j = 2 * i; j < isPrime.size(); j += i) {
                isPrime[j] = false;
            }
        }
    }
    solve();
}
