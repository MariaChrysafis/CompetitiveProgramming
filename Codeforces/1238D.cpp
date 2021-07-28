#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
 
#define ll long long
#define endl '\n'
 
using namespace std;
 
void solve() {
    long long n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'A') {
            s[i] = '0';
        } else {
            s[i] = '1';
        }
    }
    vector<pair<char,int>> v;
    char cur = s[0];
    long long cntr = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == cur){
            cntr++;
        }else{
            v.push_back({cur, cntr});
            cntr = 1;
            cur = s[i];
        }
    }
    if(cntr != 0){
        v.push_back({cur, cntr});
    }
    long long ans = (long long)s.length() * (s.length() - 1)/2;
    for(int i = 1; i < v.size(); i++){
        ans -= v[i].second;
    }
    for(int i = 0; i < v.size() - 1; i++){
        ans -= v[i].second;
    }
    for(int i = 0; i < v.size() - 1; i++){
        if(v[i] != v[i + 1]) ans++;
    }
    cout << ans << endl;
}
 
int main() {
    solve();
}
