#include <iostream>
using namespace std;
const int MOD = 1e9 + 7;
void solve(){
    int n;
    cin >> n;
    long long fact = 4;
    if(n == 1){
        fact = 2;
    }
    for(int i = 1; i <= (1 << (n - 1)); i++){
        fact *= i;
        fact %= MOD;
    }
    cout << fact << endl;
    for(int i = 0; i < (1 << (n - 1)); i ++){
        if(i % 2 == 1){
            cout << i << " " << i + (1 << (n - 1)) << " ";
        }else{
            cout << i + (1 << (n - 1)) << " " << i << " ";
        }
    }
    cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
