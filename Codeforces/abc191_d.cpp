#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>

#define ll long long
using namespace std;
void solve(){
    long double x1, y1, r1;
    cin >> x1 >> y1 >> r1;
    r1 = nextafter(r1,1000000.0);
    ll cntr = 0;
    for(ll i = ceil(y1 - r1); i <= floor(y1 + r1); i ++){
        ll endpntl, endpntr;
        long double d = r1 * r1 - (y1 - i) * (y1 - i);
        endpntr = floor(sqrt(d) + x1);
        endpntl = ceil(-sqrt(d) + x1);
        cntr += endpntr - endpntl + 1;
        //cout << endpntr - endpntl + 1 << " ";
    }
    //cout << endl;
    cout << cntr << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
