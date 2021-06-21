#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
//remember to use '\n'
void solve(){
    int n, m;
    cin >> n >> m;
    char c;
    int cntr = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> c;
            if(c == '1') cntr++;
        }
    }
    if(cntr % 2 == 0){
        cout << "NO \n";
    }else{
        cout << "YES \n";
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
