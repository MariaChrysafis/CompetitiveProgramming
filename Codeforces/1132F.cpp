#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <algorithm>
 
using namespace std;
 
void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
 
void print(vector<long long> v) {
    for (long long x: v) {
        cout << x << " ";
    }
    cout << endl;
}
 
void print(vector<char> v){
    for(char c: v) {
        cout << c << " ";
    }
    cout << endl;
}
 
void print(vector<vector<int>> v){
    for(vector<int> vec: v){
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<long long>> v){
    for(vector<long long> vec: v){
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<char>> v){
    for(vector<char> vec: v){
        print(vec);
    }
    cout << endl;
}
vector<vector<int>> fill(int n, int m, int val){
    vector<vector<int>> v;
    v.resize(n);
    for(int i = 0; i < n; i++){
        v[i].resize(m);
        for(int j = 0; j < m; j++){
            v[i][j] = val;
        }
    }
    return v;
}
string s;
vector<vector<int>> dp;
const int INF = 1e9;
int memoize(int l, int r){
    //cout << l << " " << r << endl;
    if(l > r){
        return 0;
    }
    if(dp[l][r] != -1){
        return dp[l][r];
    }
    if(l == r){
        dp[l][r] = 1;
        return 1;
    }
    int ans = 1 + memoize(l + 1, r);
    for(int i = l + 1; i <= r; i++){
        if(s[l] == s[i]) {
            ans = min(ans, memoize(l + 1, i - 1) + memoize(i, r));
        }
    }
    dp[l][r] = ans;
    return dp[l][r];
}
 
int main() {
    int n;
    cin >> n;
    dp = fill(n, n, -1);
    cin >> s;
    cout << memoize(0, n - 1) << endl;
}
