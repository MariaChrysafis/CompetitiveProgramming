#include <iostream>
#include <string>
using namespace std;
char to_char(int d){
    return '0' + d;
}
string constr(int l, int d){
    string str;
    for(int i = 0; i < l; i++){
        str += to_char(d);
    }
    return str;
}
void solve(){
    int n;
    cin >> n;
    string s = to_string(n);
    int cntr = (s.length() - 1) * 9;
    for(int i = 1; i <= 9; i++){
        if(s >= constr(s.length(), i)){
            cntr++;
        }
    }
    cout << cntr << endl;
    //cout << constr(s.length(),2) << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
