#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
bool perfect_square(int x){
    int y = sqrt(x);
    y *= y;
    return (y == x);
}
void solve(int n){
    bool fine = false;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        if(!perfect_square(a)){
            fine = true;
            //cout << "YES" << " " << a << endl;
            //return;
        }
    }
    if(!fine) cout << "NO" << endl;
    else cout << "YES" << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        solve(n);
    }
}
