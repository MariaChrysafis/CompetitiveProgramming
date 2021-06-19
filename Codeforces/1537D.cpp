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
    if(n % 2 == 1){
        cout << "Bob" << endl;
        return;
    }
    int cnt = 0;
    while(n % 2 == 0){
        n /= 2;
        cnt++;
    }
    if(n > 1){
        cout << "Alice" << endl;
    }else{
        if(cnt % 2 == 0){
            cout << "Alice" << endl;
        }else{
            cout << "Bob" << endl;
        }
    }
}
int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}
