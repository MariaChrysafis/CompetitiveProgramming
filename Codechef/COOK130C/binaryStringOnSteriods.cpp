#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
//remember to use '\n'
string s;
int manual (int rem, int modulus){
    int cntr = 0;
    for(int i = 0; i < s.length(); i++){
        if(i % modulus == rem){
            if(s[i] == '0') cntr++;
        }else{
            if(s[i] == '1') cntr++;
        }
    }
    return cntr;
}
int comp (int modulus){
    int ones[modulus];
    for(int i = 0; i < modulus; i++){
        ones[i] = 0;
    }
    int cntr = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '1'){
            ones[i % modulus]++;
        }
    }
    int myMax = -1;
    int ind = 0;
    for(int i = 0; i < modulus; i++){
        if(ones[i] > myMax){
            myMax = ones[i];
            ind = i;
        }
    }
    return ind;
}
vector<int> factors(int x){
    vector<int> v;
    for(int i = 1; i <= sqrt(x); i++){
        if(x % i == 0){
            v.push_back(i);
        }
    }
    vector<int> ans;
    for(int i = 0; i < v.size(); i++){
        ans.push_back(x/v[i]);
    }
    for(int i: v) ans.push_back(i);
    return ans;
}
void solve(){
    int n;
    cin >> n;
    cin >> s;
    vector<int> v = factors(s.length());
    int ans = n;
    for(int i = 0; i < v.size(); i++){
        //cout << comp(v[i]) << endl;
        int x = manual(comp(v[i]), v[i]);
        //cout << v[i] << " " << x << " " << comp(v[i]) << endl;
        ans = min(ans, x);
    }
    cout << ans << '\n';
    //cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
