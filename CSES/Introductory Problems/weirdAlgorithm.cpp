#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    if(n == 1){cout << n << endl; return 0;}
    cout << n << " ";
    while(true){
        ll new_n = 0;
        if(n % 2 == 1){new_n = n * 3 + 1;}
        if(n % 2 == 0){new_n = n/2;}
        swap(new_n,n);
        cout << n << " ";
        if(n == 1) return 0;
    }
}
