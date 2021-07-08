#include <iostream>
#include <cmath>
#include <set>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        long long a, b;
        cin >> a >> b;
        if(a > b) swap(a,b);
        if(b == a){
            cout << 0 << " " << 0 << endl;
            continue;
        }
        if(a % (b - a) == 0){
            cout << b - a << " " << 0 << endl;
            continue;
        }
        long long myMin = (b - a) * (a/(b - a) + (a % (b - a) != 0)) - a;
        myMin = min(myMin, a - (b - a) * (a/(b - a)));
        cout << b - a << " " << myMin << endl;
    }
}
