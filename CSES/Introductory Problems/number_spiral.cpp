#include <iostream>
#define ll long long int
using namespace std;
ll f(ll x, ll y){
    if(y > x){
        if(y % 2 == 1) return y * y - x + 1;
        return (y - 1) * (y - 1) + x;
    }else{
        if(x % 2 == 0) return x * x - y + 1;
        return (x - 1) * (x - 1) + y;
    }
    return -1;
}
int main(){
    ll t;
    cin >> t;
    while(t--){
        ll x,y;
        cin >> x >> y;
        ll ans = f(x,y);
        cout << ans << endl;
    }
}
