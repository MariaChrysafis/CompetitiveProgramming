#include <iostream>
#include <cmath>
#define ll long long int
#define MOD 1000000007
using namespace std;
ll find(ll x){
    ll cntr = 0;
    for(int i = 1; i < 15; i++){
        cntr += x/pow(5,i);
    }
    return cntr;
}
int main(){
    ll n;
    cin >> n;
    ll x = find(n);
    cout << x << endl;
}
