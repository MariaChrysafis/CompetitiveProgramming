#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int op1(int x1, int y1, int x, int y){
    return abs(x1 - x) + abs(y1 - y);
}
void solve(){
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    int myMax = max(op1(1, 1, x, y), op1(n, m, x, y));
    myMax = max(myMax, op1(n, 1, x, y));
    myMax = max(myMax, op1(1, m, x, y));
    if(myMax == op1(1, 1, x, y)){
        cout << 1 << " " << 1 << " " << n << " " << m << endl;
    }else if(myMax == op1(n, 1, x, y)){
        cout << n << " " << 1 << " " << 1 << " " << m << endl;
    }else if(myMax == op1(1, m, x, y)){
        cout << 1 << " " << m << " " << n << " " << 1 << endl;
    }else{
        cout << n << " " << m << " " << 1 << " " << 1 << endl;
    }
}
int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}
