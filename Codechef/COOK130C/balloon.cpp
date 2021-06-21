#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
//remember to use '\n'
void print(set<int> s){
    //auto it = s.begin();
    for(auto it = s.begin(); it != s.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
}
void solve(){
    int n;
    cin >> n;
    set<int> s;
    set<int> goal;
    for(int i = 1; i <= 7; i++) goal.insert(i);
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < n; i++){
        if(arr[i] >= 1 && arr[i] <= 7) s.insert(arr[i]);
        if(s == goal){
            cout << i + 1 << '\n';
            return;
        }
        //print(s);
    }
}
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
