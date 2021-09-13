#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iomanip>
#include <string>
#include <array>
#include <cassert>
#include <algorithm>
using namespace std;
void solve(){
    string s;
    cin >> s;
    bool foundZero = false;
    bool foundOne = false;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '0') {
            foundZero = true;
        } else {
            foundOne = true;
        }
    }
    if(foundZero && !foundOne){
        cout << 1 << endl;
        return;
    }
    if(foundOne && !foundZero){
        cout << 0 << endl;
        return;
    }
    //char prev = s[0];
    int cntr = 0;
    for(int i = 1; i < s.length(); i++){
        if(s[i] != s[i - 1]){
            cntr++;
        }
    }
    if(cntr == 2 && s[0] == '1'){
        cout << 1 << endl;
        return;
    }
    if(cntr == 1){
        cout << 1 << endl;
        return;
    }
    cout << 2 << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
