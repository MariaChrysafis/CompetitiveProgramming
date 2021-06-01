#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;
int conv(char c){
    if(c == '0') return 0;
    return 1;
}
void solve(){
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    char cur = '?';
    vector<pair<char,int>> v;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == cur){
            pair<char,int> p = v.back();
            v.pop_back();
            v.push_back({p.first, p.second + 1});
        }else{
            v.push_back({s[i], 1});
            cur = s[i];
        }
    }
    if(v.size() == 1){
        cout << s << endl;
        return;
    }
    pair<char,int> pr = v[0];
    if(pr.first == '1'){
        for(int i = 0; i < pr.second; i++) cout << '1';
    }else{
        int ones;
        ones = min(pr.second, m);
        int zeroes = pr.second - ones;
        for(int i = 0; i < zeroes; i++) cout << '0';
        for(int i = 0; i < ones; i++) cout << '1';
    }
    for(int i = 1; i < v.size() - 1; i++){
        pair<char,int> p = v[i];
        if(p.first == '1'){
            for(int i = 0; i < p.second; i++) cout << '1';
        }else{
            int ones;
            ones = min(p.second - (p.second % 2 == 1), 2 * m);
            int zeroes = p.second - ones;
            for(int i = 0; i < ones/2; i++) cout << '1';
            for(int i = 0; i < zeroes; i++) cout << '0';
            for(int i = 0; i < ones/2; i++) cout << '1';
        }
    }
    pr = v[v.size() - 1];
    if (pr.first == '1') {
        for(int i = 0; i < pr.second; i++) cout << '1';
    } else {
        int ones = min(pr.second, m);
        int zeroes = pr.second - ones;
        for (int i = 0; i < ones; i++) cout << '1';
        for (int i = 0; i < zeroes; i++) cout << '0';
    }
    cout << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
