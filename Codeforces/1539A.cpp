#include <iostream>
using namespace std;
void solve(){
    long long n, x, t;
    cin >> n >> x >> t;
    long long k = min(t/x, n);
    cout << n * k - k * (k + 1)/2 << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
