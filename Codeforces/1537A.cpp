#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
void solve(){
    int n;
    cin >> n;
    vector<long long> v(n);
    long long sum = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        sum += v[i];
    }
    sum -= n;
    if(sum < 0){
        cout << 1 << endl;
        return;
    }
    cout << sum << endl;
}
int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}
