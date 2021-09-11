#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <algorithm>
#include <queue>
 
using namespace std;
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    vector<pair<int,int>> s1, s2;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    if(n % 2 == 1){
        if(a[n/2] != b[n/2]){
            cout << "No\n";
            return;
        }
    }
    for(int i = 0; i < n/2; i++){
        s1.push_back(make_pair(max(a[i], a[n - i - 1]), min(a[n - i - 1], a[i])));
        s2.push_back(make_pair(max(b[i], b[n - i - 1]), min(b[n - i - 1], b[i])));
    }
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    if(s1 == s2){
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
