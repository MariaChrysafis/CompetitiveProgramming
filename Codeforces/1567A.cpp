#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
 
using namespace std;
 
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == 'U') cout << 'D';
        else if(s[i] == 'L') cout << 'L';
        else if(s[i] == 'R') cout << 'R';
        else cout << 'U';
    }
    cout << '\n';
}
 
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
