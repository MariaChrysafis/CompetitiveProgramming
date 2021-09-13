#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iomanip>
#include <string>
#include <array>
#include <cassert>
#include <algorithm>
using namespace std;
void solve(){
    int n;
    cin >> n;
    string arr[2];
    cin >> arr[0] >> arr[1];
    bool taken[n];
    for(int i = 0; i < n; i++) {
        taken[i] = false;
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        if(arr[0][i] != arr[1][i]){
            taken[i] = true;
            ans += 2;
        }
    }
    for(int i = 0; i < n - 1; i++){
        if(!taken[i] && !taken[i + 1] && arr[0][i] != arr[0][i + 1]){
            ans += 2;
            taken[i] = taken[i + 1] = true;
        }
    }
    //cout << ans << endl;
    for(int i = 0; i < n; i++){
        if(!taken[i] && arr[0][i] == '0'){
            ans++;
        }
    }
    cout << ans << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
