#include <iostream>
#include <iomanip>
#include <cmath>
#include <set>
using namespace std;
//double PI = 3.14159265358979323846;
void solve(){
    int n;
    cin >> n;
    long long arr[n];
    long long sum = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        sum += arr[i];
    }
    long long x = sum % n;
    long long y = n - x;
    cout << x * y << endl;;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
