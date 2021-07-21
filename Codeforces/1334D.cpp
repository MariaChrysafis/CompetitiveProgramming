#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
void print(vector<long long> v){
    for(long long i: v){
        cout << i << " ";
    }
    cout << endl;
}
void solve(){
    long long n, l, r;
    cin >> n >> l >> r;
    set<long long> s;
    map<long long,long long> myMap;
    for(long long i = 1; i < n; i++){
        s.insert(i * n - i * (i + 1)/2);
        myMap[i * n - i * (i + 1)/2] = i;
    }
    vector<long long> arr(r - l + 1);
    for(long long i = 0; i < arr.size(); i++){
        arr[i] = 0;
    }
    for(long long i = l; i <= r; i++){
        if(i % 2 == 1){
            arr[i - l] = *s.upper_bound((i - 1)/2);
            arr[i - l] = myMap[arr[i - l]];
        }else{
            long long mod = n - myMap[*s.lower_bound(i/2)];
            arr[i - l] = (i/2 - *s.lower_bound(i/2) + mod - 1) % mod + 1 + n - mod;
        }
    }
    if(r == n * (n - 1) + 1){
        arr[arr.size() - 1] = 1;
    }
    print(arr);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
