#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        long long n;
        cin >> n;
        long long pwr = floor(log2(n));
        long long x = pow(2,pwr);
        cout << x - 1 << endl;
    }
}
