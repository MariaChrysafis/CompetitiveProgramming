#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void solve(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    sort(arr, arr + n);
    if(n == 2) swap(arr[0], arr[1]);
    int myMin = INF;
    for(int i = 1; i < n; i++){
        myMin = min(arr[i] - arr[i - 1], myMin);
    }
    int x = 0;
    for(int i = 1; i < n; i++){
        if(arr[i] - arr[i - 1] == myMin){
            x = i;
            break;
        }
    }
    for(int i = x; i < n; i++){
        cout << arr[i] << " ";
    }
    for(int i = 0; i < x; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}
