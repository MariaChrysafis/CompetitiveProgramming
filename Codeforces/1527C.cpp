#include <iostream>
#include <map>
using namespace std;
void solve(){
    int n;
    cin >> n;
    long long arr[n];
    long long sum = 0;
    map<long long,long long> oc;
    for(long long i = 0; i < n; i++){
        cin >> arr[i];
        sum += (n - i) * oc[arr[i]];
        oc[arr[i]] += i + 1;
    }
    cout << sum << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--) solve();
}
