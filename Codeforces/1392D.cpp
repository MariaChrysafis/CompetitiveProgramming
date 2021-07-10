#include <string>
#include <iostream>
#include <vector>
using namespace std;
void print(vector<string> v){
    for(string s: v){
        cout << s << " ";
    }
    cout << '\n';
}
vector<string> split(string s){
    s += " ";
    string cur = "";
    vector<string> ans;
    for(int i = 0; i < s.length() - 1; i++){
        cur += s[i];
        if(s[i] == 'L' && s[i + 1] == 'R'){
            ans.push_back(cur);
            cur = "";
        }
    }
    if(cur != ""){
        ans.push_back(cur);
    }
    return ans;
}
string convert(string s){
    int x = -1;
    for(int i = 0; i < s.length() - 1; i++){
        if(s[i] == 'L' && s[i + 1] == 'R'){
            x = i;
            break;
        }
    }
    if(x == -1){
        return s;
    }
    string str1 = "";
    for(int i = 0; i <= x; i++){
        str1 += s[i];
    }
    string str2 = "";
    for(int i = x + 1; i < s.length(); i++){
        str2 += s[i];
    }
    return str2 + str1;
}
int penalty(string s){
    if(s == "RLL" || s == "LRR" || s == "RL"){
        return 0;
    }
    if(s == "RR" || s == "LL"){
        return 1;
    }
    int r = 0;
    int l = 0;
    for(char c: s){
        if(c == 'L'){
            l++;
        }else if(c == 'R'){
            r++;
        }
    }
    l = max(0, l - 2);
    r = max(0, r - 2);
    return l/3 + r/3 + (l % 3 != 0) + (r % 3 != 0);
}
bool monochrome(string s){
    char c = s[0];
    for(char ch: s){
        if(ch != c){
            return false;
        }
    }
    return true;
}
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(monochrome(s)){
        cout << s.length()/3 + (s.length() % 3 != 0) << endl;
        return;
    }
    vector<string> v = split(convert(s));
    int ans = 0;
    for(string s: v){
        ans += penalty(s);
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
