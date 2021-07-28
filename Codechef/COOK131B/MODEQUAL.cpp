#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>

#define ll long long
#define endl '\n'

using namespace std;
long long gcd(long long a, long long b){
    if(min(a,b) == 0) return max(a,b);
    else return gcd(max(a,b) % min(a,b), min(a,b));
}
void solve(){
    int n;
    cin >> n;
    vector<long long> arr(n);
    map<long long, long long> oc;
    long long myMin = 3e9;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        oc[arr[i]]++;
        myMin = min(myMin, arr[i]);
    }
    bool fine = false;
    for(int i = 0; i < n; i++){
        if(arr[i] != myMin && arr[i] % (arr[i] - myMin) != myMin) fine = true;
    }
    if(!fine) cout << n - oc[myMin] << endl;
    else cout << n << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
