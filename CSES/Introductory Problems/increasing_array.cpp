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
    ll cntr = 0;
    ll arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < n - 1; i++){
        if(arr[i] > arr[i + 1]){
            cntr += arr[i] - arr[i + 1];
            arr[i + 1] = arr[i];
        }
    }
    cout << cntr << endl;
 
}
