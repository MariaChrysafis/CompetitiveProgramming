#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        vector<int> v(4);
        for(int i = 0; i < 4; i++){
            cin >> v[i];
        }
        bool b = (v[0] + v[2] == 180 && v[1] + v[3] == 180);
        if(!b){
            cout << "NO\n";
        }else{
            cout << "YES\n";
        }
    }
}
