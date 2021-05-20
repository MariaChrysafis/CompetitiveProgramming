#include <iostream>
#include <cmath>
using namespace std;
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cntr = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '0'){
            cntr++;
        }
    }
    if(cntr == 1){
        cout << "BOB" << endl;
        return;
    }
    if(cntr % 4 == 2 || cntr % 4 == 0){
        cout << "BOB" << endl;
        return;
    }
    else cout << "ALICE" << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
