#include <iostream>
#include <map>
using namespace std;
void solve(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        arr[i] -= i;
        //cout << arr[i] << " ";
    }
    //cout << endl;
    //return;
    map<int,int> myMap;
    for(int i: arr){
        myMap[i]++;
    }
    long long cntr = 0;
    for(pair<int,int> p: myMap){
        long long i = p.second;
        cntr += i * (i - 1)/2;
    }
    cout << cntr << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
