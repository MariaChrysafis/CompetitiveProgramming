#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
 
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int x: v) cout << x << " ";
    cout << endl;
}
 
void print(vector<ll> v){
    for(ll x: v) cout << x << " ";
    cout << endl;
}
 
int cost(string s){
    int cntr = 0;
    for(int i = 1; i < s.length(); i++){
        if(s[i] == s[i - 1]){
            cntr++;
        }
    }
    return cntr;
}
 
const int INF = 1e9;
void solve(){
    int n;
    cin >> n;
    string orig;
    string s;
    cin >> s;
    orig = s;
    if(s.length() == 1){
        if(s[0] == '?') s[0] = 'B';
        cout << s << endl;
        return;
    }
    vector<int> v = {'B', 'R'};
    vector<string> ans;
    for(char c: v) {
        for (int i = 0; i < s.length(); i++) {
            if(s[i] != '?') continue;
            if (i == 0) {
                if (s[i + 1] == 'B') s[i] = 'R';
                else if (s[i + 1] == 'R') s[i] = 'B';
                else s[i] = c;
            } else {
                if (s[i - 1] == 'B') s[i] = 'R';
                else if (s[i - 1] == 'R') s[i] = 'B';
 
            }
        }
        ans.push_back(s);
        s = orig;
    }
    if(cost(ans[0]) < cost(ans[1])){
        swap(ans[0], ans[1]);
    }
    cout << ans.back() << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
