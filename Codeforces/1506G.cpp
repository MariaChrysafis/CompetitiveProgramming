#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
string convert(string s){
    char cur = s[0];
    string str;
    for(int i = 0; i < s.length(); i++){
        if(s[i] != cur){
            str += cur;
            cur = s[i];
        }
    }
    str += cur;
    return str;
}
void solve(){
    string s;
    cin >> s;
    //s = convert(s);
    map<char,int> oc;
    for(char c: s) oc[c]++;
    bool hv[s.length()];
    for(int i = 0; i < s.length(); i++){
        hv[i] = false;
    }
    string ans = "";
    for(int i = 0; i < s.length(); i++){
        if(hv[i]){
            continue;
        }
        if(oc[s[i]] == 1){
            ans += s[i];
            oc[s[i]]--;
            hv[i] = true;
            continue;
        }
        int nxt = -1;
        for(int j = i + 1; j < s.length(); j++){
            if(s[j] > s[i] && !hv[j]){
                nxt = j;
                break;
            }
        }
        if(nxt == -1){
            //its best to keep it as is
            for(int j = 0; j < s.length(); j++){
                if(s[j] == s[i] && !hv[j]){
                    hv[j] = true, oc[s[j]]--;
                }
            }
            ans += s[i];
        }else{
            map<char,int> copy;
            for(auto p: oc){
                copy[p.first] = p.second;
            }
            bool fine = true;
            for(int j = i; j < nxt; j++){
                if(hv[j]) continue;
                copy[s[j]]--;
                if(oc[s[j]] <= 1){
                    fine = false;
                }
            }
            for(int j = i; j < nxt; j++){
                if(!hv[j] && copy[s[j]] == 0){
                    fine = false;
                }
            }
            if(fine){
                for(int j = i; j < nxt; j++){
                    if(!hv[j]){
                        oc[s[j]]--;
                    }
                    hv[j] = true;
                }
                if(oc[s[i]] == 0){
                    //cout << i << " " << nxt << endl;
                    ans += s[i];
                }
            }else{
                ans += s[i];
                for(int j = 0; j < s.length(); j++){
                    if(s[j] == s[i] && !hv[j]){
                        hv[j] = true;
                    }
                }
                oc[s[i]] = 0;
            }
        }
    }
    cout << ans << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
