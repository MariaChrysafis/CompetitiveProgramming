#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
void put(string s){
    cout << s << endl;
}
void print(vector<int> a){
    for(int i: a){
        cout << i << " ";
    }
    cout << endl;
}
vector<char> alphabet;
int GCD(int a, int b){
    if(min(a,b) == 0) return max(a,b);
    int mx = max(a,b);
    int mn = min(a,b);
    return GCD(mx % mn, min(a,b));
}
pair<int,int> conv(int a, int b){
    if(a == 0){
        return {0, 1};
    }
    if(b == 0){
        return {1,0};
    }
    return {a/GCD(a,b), b/GCD(a,b)};
}
void solve(){
    //cout << GCD(3,2) << endl;
    int n;
    cin >> n;
    string s;
    cin >> s;
    int dp[n];
    for(int i = 0; i < n; i++) dp[i] = 1;
    dp[0] = 1;
    map<pair<int,int>, int> myMap;
    map<pair<int,int>, bool> vis;
    int d = (s[0] == 'D');
    int k = 1 - d;
    myMap[{d,k}] = 0, vis[{d,k}] = 1;
    //cout << d << " " << k << " " << dp[0] << endl;
    for(int i = 1; i < s.length(); i++){
        if(s[i] == 'D') d++;
        else k++;
        int p1 = conv(d, k).first;
        int p2 = conv(d, k).second;
        dp[i] = dp[myMap[{p1,p2}]] + (vis[{p1,p2}]);
        //cout << d << " " << k << " " << dp[i] << endl;
        myMap[{p1,p2}] = i, vis[{p1,p2}] = 1;
        //cout << myMap[{1,1}] << endl;
    }
    for(int i: dp){
        cout << i << " ";
    }
    cout << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(char c = 'a'; c <= 'z'; c++) alphabet.push_back(c);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
