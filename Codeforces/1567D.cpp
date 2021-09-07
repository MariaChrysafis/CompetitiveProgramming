#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
 
using namespace std;
vector<int> dig;
int rec(int a, int b){
    if(b == 1) {
        cout << a << " ";
        return a;
    }
    for(int i = dig.size() - 1; i >= 0; i--){
        if(a - dig[i] >= b - 1){
            cout << dig[i] << " ";
            return rec(a - dig[i], b - 1);
        }
    }
}
void solve(){
    int a, b;
    cin >> a >> b;
    rec(a, b);
    cout << endl;
}
 
int main() {
    for(int i = 0; i < 10; i++){
        dig.push_back(pow(10, i));
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
