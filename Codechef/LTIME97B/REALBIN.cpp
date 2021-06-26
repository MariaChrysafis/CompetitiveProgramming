#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
map<long long, bool> myMap;
void solve(){
    long long a, b;
    cin >> a >> b;
    if(myMap[b]){
        cout << "Yes" << '\n';
    }else{
        cout << "No" << '\n';
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long powr = 1;
    for(int i = 0; i < 60; i++){
        myMap[powr] = true;
        powr *= 2;
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
