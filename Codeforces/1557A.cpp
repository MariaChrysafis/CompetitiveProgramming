#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
void solve(){
    int n;
    cin >> n;
    vector<double> v(n);
    int myMax = -INT_MAX;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        myMax = max(myMax, (int)v[i]);
    }
    int ind = 0;
    for(int i = 0; i < n; i++){
        if(v[i] == myMax){
            ind = i;
            break;
        }
    }
    double sum1 = 0;
    for(int i = 0; i < n; i++){
        if(i != ind) {
            sum1 += v[i];
        }
    }
    sum1 /= (n - 1);
    cout << setprecision(30) << sum1 + v[ind] << '\n';
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
