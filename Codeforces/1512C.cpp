#include <iostream>
#include <map>
#include <vector>
using namespace std;
void solve(){
    int a, b;
    cin >> a >> b;
    string s;
    cin >> s;
    for(int i = 0; i < s.length()/2; i++){
        if(s[i] != s[s.length() - 1 - i] && s[i] != '?' && s[s.length() - 1 - i] != '?'){
            cout << -1 << endl;
            return;
        }
        if(s[i] != s[s.length() - 1 - i] && s[i] == '?' && s[s.length() - 1 - i] != '?'){
            s[i] = s[s.length() - 1 - i];
        }
        if(s[i] != s[s.length() - 1 - i] && s[i] != '?' && s[s.length() - 1 - i] == '?'){
            s[s.length() - 1 - i] = s[i];
        }
    }
    int a1 = 0;
    int b1 = 0;
    for(char c: s){
        if(c == '0'){
            a1++;
        }else if(c == '1'){
            b1++;
        }
    }
    if(a1 > a || b1 > b){
        cout << -1 << endl;
        return;
    }
    if((int)s.length() % 2 == 1 && s[s.length()/2] == '?'){
        if((a - a1) % 2 == 1){
            s[s.length()/2] = '0';
        }else{
            s[s.length()/2] = '1';
        }
        if(s[s.length()/2] == '1') b1++;
        else a1++;
    }
    for(int i = 0; i < s.length()/2; i++){
        if(s[i] == '?'){
            if(a > a1){
                s[i] = s[s.length() - 1 - i] =  '0';
                a1 += 2;
            }else{
                s[i] = s[s.length() - 1 - i] = '1';
                b1 += 2;
            }
        }
    }
    if(a == a1 && b == b1){
        cout << s << endl;
    }else{
        cout << -1 << endl;
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
