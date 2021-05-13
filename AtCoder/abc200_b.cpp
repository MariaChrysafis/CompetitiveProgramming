#include <iostream>
using namespace std;
long long ans(long long n, long long k){
    if(k == 0){
        return n;
    }
    if(k == 1){
        if(n % 200 == 0) return n/200;
        else return n * 1000 + 200;
    }
    if(n % 200 == 0) return ans(n/200, k - 1);
    return ans(n * 5 + 1, k - 2);
}
int main(){
    long long n, k;
    cin >> n >> k;
    long long x = ans(n , k);
    cout << x << endl;
}
