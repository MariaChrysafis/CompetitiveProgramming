#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;
void solve(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    vector<int> ans;
    for(int i = 0; i < n; i++){
        if(arr[i] != 1){
            while(!ans.empty() && ans.back() + 1 != arr[i]){
                ans.pop_back();
            }
            if(!ans.empty()) ans.pop_back();
        }
        ans.push_back(arr[i]);
        for(int i = 0; i < ans.size() - 1; i++){
            cout << ans[i] << ".";
        }
        cout << ans.back();
        cout << endl;
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
