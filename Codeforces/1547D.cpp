#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;
long long add(long long x, long long y){
    long long ans = 0;
    for(long long i = 0; i < 30; i++){
        bool bit1 = (x & (1 << i));
        bool bit2 = (y & (1 << i));
        if(!bit1 && bit2){
            ans += (1 << i);
        }
    }
    return ans;
}
void solve(){
    int n;
    cin >> n;
    long long arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    vector<int> ans;
    int best = arr[0];
    ans.push_back(0);
    for(int i = 1; i < n; i++){
        long long chng = add(arr[i], best);
        ans.push_back(chng);
        best = arr[i] ^ chng;
    }
    for(int i: ans){
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
