#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
using namespace std;
 
void solve() {
    int n;
    cin >> n;
    vector<long long> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < n - 1; i++){
        if(i != 0 && (arr[i] ^ arr[i + 1]) < arr[i - 1]){
            cout << 1 << endl;
            return;
        }
        if(i != n - 2 && (arr[i] ^ arr[i + 1]) > arr[i + 2]){
            cout << 1 << endl;
            return;
        }
    }
    for(int i = 0; i < n - 1; i++){
        if(i > 1 && (arr[i] ^ arr[i + 1]) == arr[i - 1] && n != 3){
            cout << 2 << endl;
            return;
        }
        if(i != n - 2 && (arr[i] ^ arr[i + 1]) == arr[i + 2] && n != 3){
            cout << 2 << endl;
            return;
        }
    }
    int ans = 1e9;
    for(int l = 0; l < n; l++){
        for(int r = l + 1; r < n; r++){
            for(int cut = l; cut < r; cut++){
                int left = 0;
                int right = 0;
                for(int i = l; i <= cut; i++){
                    left ^= arr[i];
                }
                for(int i = cut + 1; i <= r; i++){
                    right ^= arr[i];
                }
                if(left > right){
                    ans = min(ans, r - l - 1);
                }
            }
        }
    }
    if(ans == 1e9) cout << -1 << endl;
    else cout << ans << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
