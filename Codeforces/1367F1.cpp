#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <algorithm>
#include <queue>

using namespace std;
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    map<int,int> oc;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        oc[v[i]] = i;
    }
    int ind = 0;
    for(pair<int,int> p: oc){
        v[p.second] = ind;
        ind++;
    }
    oc.clear();
    for(int i = 0; i < v.size(); i++){
        oc[v[i]] = i;
    }
    int dp[n];
    dp[0] = 1;
    int myMax = 1;
    for(int i = 1; i < v.size(); i++){
        if(oc[i - 1] < oc[i]) dp[i] = dp[i - 1] + 1;
        else dp[i] = 1;
        myMax = max(myMax, dp[i]);
    }
    cout << n - myMax << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
