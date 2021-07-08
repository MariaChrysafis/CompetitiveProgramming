#include <iostream>
#include <iomanip>
#include <cmath>
#include <set>
using namespace std;
bool query(int x){
    cout << x << '\n';
    bool y;
    cin >> y;
    return y;
}
void solve(){
    int n, k;
    cin >> n >> k;
    bool b = query(0);
    if(b){
        return;
    }
    for(int i = 0; i <= n; i++){
        bool b = query(i ^ (i + 1));
        if(b){
            return;
        }
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
