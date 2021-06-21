#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
//remember to use '\n'
int main(){
    int t;
    cin >> t;
    while(t--) {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        if (x2 >= x1 && y2 >= y1 && z2 <= z1) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
}
