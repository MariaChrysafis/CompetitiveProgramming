#include <bitset>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <map>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
pair<int,int> children(int node){
    return {2 * node, 2 * node + 1};
}
int parent(int node){
    if(node % 2 == 0){
        return node/2;
    }else{
        return (node - 1)/2;
    }
}
vector<int> dp;
string s;
map<int,int> to_ind;
map<int,int> to_ind_rev;
void update(int x){
    //cout << x << " ";
    if(x <= 0) return;
    //cout << x << " ";
    int ind = to_ind[x];
    if(s[ind] == '?') dp[x] = dp[2 * x + 1] + dp[2 * x];
    else if(s[ind] == '0') dp[x] = dp[2 * x + 1];
    else dp[x] = dp[2 * x];
    update(parent(x));
}
void solve(){
    int k;
    cin >> k;
    cin >> s;
    dp.resize(s.length() * 2 + 2);
    for(int i = s.length() + 1; i <= 2 * s.length() + 1; i++){
        dp[i] = 1;
    }
    int ind = 0;
    for(int i = s.length(); i >= 1; i--){
        if(s[ind] == '?') dp[i] = dp[2 * i + 1] + dp[2 * i];
        else if(s[ind] == '0') dp[i] = dp[2 * i + 1];
        else dp[i] = dp[2 * i];
        to_ind[i] = ind;
        to_ind_rev[ind] = i;
        ind++;
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int a;
        cin >> a;
        char c;
        cin >> c;
        a--;
        s[a] = c;
        update(to_ind_rev[a]);
        //cout << endl;
        cout << dp[1] << endl;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
