#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int find_index(vector<int> v, int val){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == val){
            return i;
        }
    }
    return -1;
}
vector<int> reverse(vector<int> v, int pref){
    cout << pref + 1 << " ";
    reverse(v.begin(), v.begin() + pref + 1);
    return v;
}
void solve(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 != (i + 1) % 2) {
            cout << "-1\n";
            return;
        }
    }
    cout << 5 * (n/2) << endl;
    for(int i = n/2; i >= 1; i--){
        int pos2 = 2 * i + 1;
        int pos1 = 2 * i;
        arr = reverse(arr, find_index(arr, pos2));
        //print(arr);
        arr = reverse(arr, find_index(arr, pos1) - 1);
        //print(arr);
        arr = reverse(arr, find_index(arr, pos1) + 1);
        //print(arr);
        arr = reverse(arr, 2);
        //print(arr);
        arr = reverse(arr, pos1);
        //print(arr);
    }
    //print(reverse(arr, 2));
    //cout << 0 << endl;
    cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
 
}
