#include <iostream>
#include <iomanip>
#include <cmath>
#include <set>
using namespace std;
long double ans = 0;
const double SMOL = 1e-10;
long double scale = 1e6;
bool equal(double a, double b){
    return (abs(a - b) <= SMOL);
}
bool lessThanOrEqualTo(double a, double b){
    if(equal(a,b)) return true;
    else return (a < b);
}
void f(long double c, long double m, long double p, long double v, long double probability, long long cntr){
    ans += probability * p * cntr;
    if(!equal(c, 0.0)){
        if(lessThanOrEqualTo(c,v)){
            if(m != 0) f(0.0, m + c/2.0, p + c/2.0, v, probability * c, cntr + 1);
            else return f(0.0, m, p + c, v, probability * c, cntr + 1);
        }else{
            if(m != 0) f(c - v, m + v/2.0 , p + v/2.0, v, probability * c, cntr + 1);
            else f(c - v, m , p + v, v, probability * c, cntr + 1);
        }
    }
    if(!equal(m, 0.0)){
        if(lessThanOrEqualTo(m, v)){
            if(c != 0) f(c + m/2.0, 0.0, p + m/2.0, v, probability * m, cntr + 1);
            else f(c, 0.0, p + m, v, probability * m, cntr + 1);
        }else{
            if(c != 0) f(c + v/2.0, m - v, p + v/2.0, v, probability * m, cntr + 1);
            else f(c, m - v, p + v, v, probability * m, cntr + 1);
        }
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        long double c, m, p, v;
        cin >> c >> m >> p >> v;
        f(c, m, p, v, 1, 1);
        cout << setprecision(30) << ans << endl;
        ans = 0;
    }
}
