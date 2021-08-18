#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
 
struct lex_compare {
    bool operator() (const string lhs, const string rhs) const {
        if(lhs.length() == rhs.length()){
            return (lhs < rhs);
        }
        return (lhs.length() < rhs.length());
    }
};
 
set<string, lex_compare> same;
set<string, lex_compare> almost_same;
 
void solve(){
    string s;
    int k;
    cin >> s >> k;
    if(k == 1){
        cout << *same.lower_bound(s) << endl;
    }else{
        cout << *almost_same.lower_bound(s) << endl;
    }
}
 
vector<vector<string>> vec;
 
void rec(string s, int len){
    vec[s.length()].push_back(s);
    if(s.length() == len){
        return;
    }
    rec(s + '1', len);
    rec(s + '0', len);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(char i = '1'; i <= '9'; i++){
        string s = "";
        for(int j = 1; j <= 10; j++) {
            s += i;
            same.insert(s);
            almost_same.insert(s);
        }
    }
    vec.resize(12);
    rec("", 11);
    for(int digits = 2; digits <= 11; digits++){
        for(char i = '0'; i <= '9'; i++){
            for(char j = '0'; j <= '9'; j++){
                if(i >= j) continue;
                for(string s: vec[digits]){
                    string ans = "";
                    for(char c: s){
                        if(c == '0'){
                            ans += i;
                        }else{
                            ans += j;
                        }
                    }
                    if(ans[0] != '0') {
                        almost_same.insert(ans);
                    }
                }
            }
        }
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
