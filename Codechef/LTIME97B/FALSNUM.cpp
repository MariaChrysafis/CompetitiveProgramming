#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
void solve(){
    string s;
    cin >> s;
    if(s[0] != '1'){
        cout << "1" + s << '\n';
    }else{
        cout << s[0] << "0";
        for(int i = 1; i < s.length(); i++) cout << s[i];
        cout << '\n';
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
