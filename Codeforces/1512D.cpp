#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
vector<ll> arr;
ll SUM(){
    ll sum = 0;
    for(ll x: arr){
        sum += x;
    }
    return sum;
}
ll binSearch(ll l, ll r, ll x){
    if(l > r){
        return -1;
    }
    ll m = (l + r)/2;
    if(arr[m] == x){
        return m;
    }
    if(arr[m] > x){
        return binSearch(0, m - 1, x);
    }
    if(arr[m] < x){
        return binSearch(m + 1, r, x);
    }
}
void solve(){
    bool found = false;
    ll n;
    cin >> n;
    arr.resize(n + 2);
    for(int i = 0; i < n + 2; i++){
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    ll sum = SUM();
    for(int i = 0; i < n + 2; i++){
        ll x = binSearch(0, n + 1, sum - 2 * arr[i]);
        if(x != -1 && i != x){
            found = true;
            for(int j = 0; j < n + 2; j++){
                if(j != i && j != x){
                    cout << arr[j] << " ";
                }
            }
            cout << endl;
            break;
        }
    }
    if(!found){
        cout << -1 << endl;
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
