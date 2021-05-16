#include <iostream>
#include <cmath>
using namespace std;
long long pwr(long long x){
    return x * x * x * x;
}
long long ans(long long op, long long fi){
    if(fi == 0) return pwr(op);
    if(fi == 1) return pwr(op) - pwr(op - 1);
    if(fi == 2) return - pwr(op) + pwr(op - 2) + 2 * ans(op, fi - 1);
    if(fi == 3) return pwr(op) - pwr(op - 3) - 3 * ans(op, fi - 2) + 3 * ans(op, fi - 1);
    if(fi == 4) return 24;
    else return 0;
}
int main(){
    string s;
    cin >> s;
    long long op = 0;
    long long fi = 0;
    for(char c: s){
        if(c != 'x') op++;
        if(c == 'o') fi++; 
    }
    cout << ans(op, fi) << endl;
    //cout << fi << " " << op << endl;
}
