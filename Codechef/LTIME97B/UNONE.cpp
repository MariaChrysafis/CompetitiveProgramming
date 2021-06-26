#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<int> evens, odd;
    for(int i = 0; i < n; i++){
        if(v[i] % 2 == 0){
            evens.push_back(v[i]);
        }else{
            odd.push_back(v[i]);
        }
    }
    print(evens), print(odd);
    cout << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
