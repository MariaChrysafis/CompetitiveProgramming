#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
/*
 * a_1 = a_2 & a_3 ... & a_n
 * a_1 = a_1 & a_2 & a_3 ... & a_n
 * a_1 & a_2 = a_3 & a_4 ... & a_n
 * a_1 & a_2 = a_1
 * a_1 & a_2 & a_3 = a_1
 *
*/ 
const ll MOD = pow(10,9) + 7;
ll fact[200001];
void fill(){
    fact[0] = 1;
    for(int i = 1; i < 200001; i++){
        fact[i] = fact[i - 1] * i;
        if(fact[i] >= MOD){
            fact[i] %= MOD;
        }
    }
}
void solve(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    sort(arr, arr + n);
    //find possible a_1s
    ll cntr = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == arr[0]){
            cntr++;
        }
        if((arr[i] & arr[0]) != arr[0]){
            cout << 0 << endl;
            return;
        }
    }
    cntr *= (cntr - 1);
    cntr %= MOD;
    cout << (cntr * fact[n - 2]) % MOD << endl;
}
int main(){
    fill();
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
