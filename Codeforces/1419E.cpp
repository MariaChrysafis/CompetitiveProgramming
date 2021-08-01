#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
int gcd(int a, int b){
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
vector<int> primes;
vector<int> powers;
vector<vector<int>> all;
vector<int> dum;
void rec(vector<int> v, int cur){
    if(cur == v.size()){
        //print(v);
        if(v != dum) all.push_back(v);
        return;
    }
    for(int i = 0; i <= powers[cur]; i++){
        v[cur] = i;
        rec(v, cur + 1);
    }
}
bool isCube(int n){
    for(int i = 2; i <= sqrt(n); i++){
        if(i * i * i == n){
            return true;
        }
    }
    return false;
}
void solve(){
    int orig;
    int n;
    cin >> n;
    orig = n;
    primes.clear();
    powers.clear();
    all.clear();
    const int MAX = sqrt(n);
    for(int i = 2; i <= MAX; i++){
        if(n % i == 0){
            primes.push_back(i);
            powers.push_back(0);
        }
        while(n % i == 0){
            n /= i;
            powers.back()++;
        }
    }
    if(n != 1){
        primes.push_back(n);
        powers.push_back(1);
    }
    //print(primes), print(powers);
    n = orig;
    dum.resize(primes.size());
    for(int i = 0; i < primes.size(); i++){
        dum[i] = 0;
    }
    rec(dum, 0);
    //print(primes), print(powers);
    set<int> factors;
    for(vector<int> vec: all){
        int ans = 1;
        for(int i = 0; i < vec.size(); i++){
            ans *= pow(primes[i], vec[i]);
        }
        factors.insert(ans);
    }
    int lead = 0;
    vector<int> ans;
    if(primes.size() == 2 && factors.size() == 3){
        lead = 1;
        //cout << *factors.begin() << " ";
        ans.push_back(*factors.begin());
        factors.erase(factors.begin());
    }
    int cur = n;
    factors.erase(n);
    //cout << n << " ";
    ans.push_back(n);
    while(!factors.empty()){
        for(int i: factors){
            if(gcd(cur, i) != 1){
                factors.erase(i);
                cur = i;
                ans.push_back(cur);
                break;
            }
        }
    }
    print(ans);
    cout << lead << endl;
    //cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
