#include <iostream>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int l, h;
        cin >> l >> h;
        string s;
        cin >> s;
        int need = h;
        int cntr = 0;
        for(int i = 0; i < l; i++){
            if(need < 0) break;
            if(s[i] == '0'){
                cntr++;
            }else{
                if(cntr >= need/2 + 1){
                    need = 2 * (need - cntr);
                }
                cntr = 0;
            }
        }
        if(cntr >= need/2 + 1){
            need = 2 * (need - cntr);
        }
        if(need <= 0){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
}
