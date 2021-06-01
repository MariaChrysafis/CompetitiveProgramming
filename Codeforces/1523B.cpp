#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;
int slv(int ind1, int ind2){
    for(int i = 0; i < 3; i++){
        cout << "1 " << ind1 << " " << ind2 << endl;
        cout << "2 " << ind1 << " " << ind2 << endl;
    }
}
void solve(){
    int n;
    cin >> n;
    int arr[n];
    for(int i= 0; i < n; i++){
        cin >> arr[i];
    }
    cout << 3 * n << endl;
    for(int i = 0; i < n/2; i++){
        //cout << 2 * i << " " << 2 * i + 1 << endl;
        for(int j = 0; j < 3; j++){
            cout << "1 " << 2 * i + 1 << " " << 2 * i + 2 << endl;
            cout << "2 " << 2 * i + 1 << " " << 2 * i + 2 << endl;
        }    
    }
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
