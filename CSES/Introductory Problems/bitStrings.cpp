#include <iostream>
#define ll long long int
#define MOD 1000000007
using namespace std;
ll powMod(ll x, ll y){
    ll cur = 1;
    for(int i = 0; i < y; i++){
        cur *= x;
        cur %= MOD;
    }
    return cur;
}
int main(){
    int n;
    cin >> n;
    int x = powMod(2,n);
    cout << x << endl;
}
