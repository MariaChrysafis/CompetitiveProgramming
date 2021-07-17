#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
 
string yesNo(bool b){
    if(b) return "Yes";
    else return "No";
}
 
void print(vector<int> v) {
    for (int i: v) cout << i << ' ';
    cout << endl;
}
 
int to_int(char c){
 
}
 
void solve(){
    string s;
    cin >> s;
    char myMax = '0';
    for(char c: s){
        myMax = max(myMax, c);
    }
    cout << myMax - '0' << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
 
/*
 * Notes to self:
 * before implementing THINK
 * Long Long vs Int?
 */
