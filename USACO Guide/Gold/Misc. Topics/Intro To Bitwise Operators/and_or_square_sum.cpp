#include <iostream>
#include <algorithm>
using namespace std;
void solve(){
    int n;
    cin >> n;
    long long arr[20];
    for(int i = 0; i < 20; i++){
        arr[i] = 0;
    }
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        for(int j = 0; j < 20; j++){
            if(x & (1 << j)){
                arr[j]++;
            }
        }
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        long long cntr = 0;
        for(int j = 0; j < 20; j++){
            if(arr[j] > 0){
                arr[j]--;
                cntr += (1 << j);
            }
        }
        ans += cntr * cntr;
    }
    cout << ans << endl;
}
int main(){
    solve();
}
