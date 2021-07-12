#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <set>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void print(vector<bool> v){
    for(bool i: v){
        cout << i << " ";
    }
    cout << endl;
}
string yesNo(bool b){
    if(b) return "YES";
    return "NO";
}
void solve(){
    map<int,int> oc;
    int n;
    cin >> n;
    vector<int> arr;
    arr.resize(2 * n);
    vector<bool> hv(2 * n);
    for(int i = 0; i < 2 * n; i++){
        cin >> arr[i];
        oc[arr[i]] = i;
        hv[i] = false;
    }
    vector<int> block;
    vector<int> v;
    for(int i = 2 * n; i >= 1; i--){
        int x = oc[i];
        if(hv[x]) continue;
        for(int j = x; j < 2 * n; j++){
            if(!hv[j]){
                hv[j] = true;
                block.push_back(j);
            }else{
                break;
            }
        }
        v.push_back(block.size());
        block.clear();
    }
    vector<vector<bool>> dp;
    dp.resize(v.size() + 1);
    for(int i = 0; i < dp.size(); i++){
        dp[i].resize(n + 1);
    }
    for(int i = 0; i < dp.size(); i++){
        dp[i][0] = true;
    }
    for(int i = 1; i <= n; i++){
        dp[0][i] = false;
    }
    for(int i = 1; i <= v.size(); i++){
        for(int j = 1; j <= n; j++){
            if(j < v[i - 1]){
                dp[i][j] = dp[i - 1][j];
            }else{
                dp[i][j] = dp[i - 1][j] || (dp[i - 1][j - v[i - 1]]);
            }
        }
    }
    cout << (dp[v.size()][n] ? "YES": "NO") << '\n';
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
