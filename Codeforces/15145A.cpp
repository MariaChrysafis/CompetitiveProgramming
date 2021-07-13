#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
map<int,vector<int>> construct(vector<int> v){
    map<int,vector<int>> myMap;
    for(int i = 0; i < v.size(); i++){
        myMap[v[i]].push_back(i);
    }
    return myMap;
}
void solve(){
    int n;
    cin >> n;
    vector<int> arr(n);
    set<int> s;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        s.insert(arr[i]);
    }
 
    map<int,vector<int>> myMap1 = construct(arr);
    sort(arr.begin(), arr.end());
    map<int, vector<int>> myMap2 = construct(arr);
    for(auto it = s.begin(); it != s.end(); it++){
        int odd = 0;
        for(int i: myMap1[*it]){
            if(i % 2 == 1){
                odd++;
            }
        }
        int odd1 = 0;
        for(int i: myMap2[*it]){
            if(i % 2 == 1){
                odd1++;
            }
        }
        if(odd1 != odd){
            cout << "NO \n";
            return;
        }
    }
    cout << "YES \n";
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
