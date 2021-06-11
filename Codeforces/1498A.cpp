#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
#define ll unsigned long long int
ll GCD(ll a, ll b){
    if(min(a,b) == 0) return max(a,b);
    return GCD(max(a,b) % min(a,b), min(a,b));
}
ll sum_of_digits(ll n){
    ll sum = 0;
    while(n != 0){
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
ll gcd_sum(ll a){
    return GCD(a, sum_of_digits(a));
}
int main(){
    int t;
    cin >> t;
    //cout << gcd_sum(2) << endl;
    while(t--){
        ll n;
        cin >> n;
        for(ll i = 0; i <= 3; i++){
            if(gcd_sum(n + i) != 1){
                cout << n + i << endl;
                break;
            }
        }
    }
}
