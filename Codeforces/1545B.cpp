#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
const int MOD = 998244353;
const int MAX =1e5 + 1;
vector<int> fact;
long long mult(long long a, long long b){
    return (a * b) % MOD;
}
long long binpow(long long x, long long y){
    long long res = x;
    long long ans = 1;
    while(y > 0){
        if(y & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
long long inv(long long a){
    return binpow(a, MOD - 2);
}
long long combo(long long a, long long b){
    return (fact[a] * inv((mult(fact[b], fact[a - b])))) % MOD;
}
void solve(){
    int len;
    cin >> len;
    string s;
    cin >> s;
    vector<vector<char>> ans;
    vector<char> block;
    char prev = s[0];
    for(int i = 0; i < s.length(); i++){
        if(s[i] == prev){
            block.push_back(s[i]);
        }else{
            ans.push_back(block);
            block.clear();
            block.push_back(s[i]);
            prev = s[i];
        }
    }
    if(block.size() != 0){
        ans.push_back(block);
    }
    int zero = 0;
    int one = 0;
    for(vector<char> v: ans){
        if(v[0] == '0') zero += v.size();
        else one += (int)v.size()/2;
    }
    cout << combo(zero + one, one) << endl;
}
int main() {
    //cout << binpow(3, 3) << endl;
    fact.push_back(1);
    int x = 1;
    while(fact.size() != MAX){
        fact.push_back(mult(fact.back(), x));
        x++;
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
