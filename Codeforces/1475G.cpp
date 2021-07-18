#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << ' ';
    }
    cout << endl;
}
vector<int> divisors(int x){
    vector<int> div;
    for(int j = 1; j <= sqrt(x); j++){
        if(x % j == 0) {
            div.push_back(j);
        }
    }
    int sz = div.size();
    for(int j = 0; j < sz; j++){
        div.push_back(x / div[j]);
    }
    return div;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> dp(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    dp[0] = 1;
    int lastOc[200005];
    for(int i = 0; i < 200005; i++){
        lastOc[i] = 0;
    }
    lastOc[v[0]] = 1;
    int myMax = 1;
    //cout << 1 << " ";
    for(int i = 1; i < n; i++){
        vector<int> div;
        dp[i] = 1;
        for(int j = 1; j <= sqrt(v[i]); j++){
            if(v[i] % j == 0) {
                int x = lastOc[j];;
                if(x != 0) dp[i] = max(dp[x - 1] + 1, dp[i]);
                int y = lastOc[v[i]/j];
                if(y != 0) dp[i] = max(dp[y - 1] + 1, dp[i]);
            }
        }
        lastOc[v[i]] = i + 1;
        myMax = max(myMax, dp[i]);
    }
    cout << n - myMax << '\n';
 
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
