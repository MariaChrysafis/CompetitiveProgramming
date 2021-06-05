#include <iostream>
using namespace std;
void solve(){
    int n, k;
    cin >> n >> k;
    int arr[n];
    for(int i = 0; i < n; i++) cin >> arr[i];
    while(k--){
        int x = -1;
        for(int i = 0; i < n; i++){
            if(arr[i] >= 1){
                x = i;
                break;
            }
        }
        if(x == -1) break;
        arr[x]--;
        arr[n - 1]++;
    }
    for(int i: arr){
        cout << i << " ";
    }
    cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
