//
//  main.cpp
//  testing
//
//  Created by Maria Chrysafis on 8/30/21.
//
 
#include <iostream>
using namespace std;
void solve(int a, int b){
    if(abs(b - a) % 2 == 1){
        cout << "-1\n";
        return;
    }
    if(a == 0 && b == 0){
        cout << "0\n";
        return;
    }
    if(a == b){
        cout << "1\n";
        return;
    }
    cout << "2\n";
    return;
}
int main(int argc, const char * argv[]) {
    int t;
    cin >> t;
    while(t--){
        int a, b;
        cin >> a >> b;
        solve(a, b);
    }
}
