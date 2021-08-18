#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
string construct(string s, string t){
    //s without t
    string ans;
    for(int i = 0; i < s.length(); i++){
        bool fine = true;
        for(char c: t){
            if(s[i] == c){
                fine = false;
            }
        }
        if(!fine) continue;
        ans += s[i];
    }
    return ans;
}
string create(string s, string t){
    string pref = "";
    string ans = "";
    for(int i = 0; i < t.length(); i++){
        ans += construct(s, pref);
        pref += t[i];
    }
    return ans;
}
void solve(){
    string s;
    cin >> s;
    map<char, int> lastOc;
    for(int i = 0; i < s.length(); i++){
        lastOc[s[i]] = i;
    }
    vector<pair<int,char>> v;
    for(pair<char,int> p: lastOc){
        v.push_back({p.second, p.first});
    }
    sort(v.begin(), v.end());
    string t;
    for(int i = 0; i < v.size(); i++){
        t += v[i].second;
    }
    map<char,int> oc;
    for(int i = 0; i < s.length(); i++){
        oc[s[i]]++;
    }
    for(int i = 0; i < t.length(); i++){
        if(oc[t[i]] % (i + 1) != 0){
            cout << "-1\n";
            return;
        }
        oc[t[i]] /= (i + 1);
    }
    map<int,int> soFar;
    string ans;
    for(int i = 0; i < s.length(); i++){
        if(soFar[s[i]] + 1 > oc[s[i]]){
            break;
        }
        soFar[s[i]]++;
        ans += s[i];
    }
    if(create(ans, t) != s){
        cout << "-1\n";
        return;
    }
    cout << ans << " " << t << endl;
    //cout << create(ans, t) << endl;
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
