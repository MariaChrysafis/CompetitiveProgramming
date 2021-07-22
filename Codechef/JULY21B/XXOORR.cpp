#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
void solve(){
    int n, k;
    cin >> n >> k;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int ans = 0;
    for(int i = 0; i < 30; i++){
        int cntr = 0;
        for(int j = 0; j < n; j++) {
            if (arr[j] & (1 << i)) {
                cntr++;
            }
        }
        ans += cntr/k + (cntr % k != 0);
    }
    cout << ans << endl;
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
