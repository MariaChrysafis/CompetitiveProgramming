#include <iostream>
using namespace std;
long long Floor(long long a, long long b){
    if(a > 0 && b > 0) return a/b;
    if(a < 0 && b < 0) return abs(a)/abs(b);
    return a/b - (abs(a) % abs(b) != 0);
}
long long Ceil(long long a, long long b){
    return Floor(a,b) + (abs(a) % abs(b) != 0);
}
long long x, y, a, b;
bool valid(long long e){
    // d <= x - ae/(b - a)
    // d >= y - be/(a - b)
    // d >= 0
    // d <= e
    long long myMin = min(Floor(x - a * e, b - a), e); //right
    long long myMax = max(Ceil(y - b * e, a - b), 0ll); //left
    return (myMin >= myMax);
}
long long binSearch(long long l, long long r){
    if(l > r){
        return 0;
    }
    if(l == r){
        if(valid(l)) return l;
        else return 0;
    }
    int m = (l + r + 1)/2;
    if(valid(m)){
        return binSearch(m, r);
    }else{
        return binSearch(l, m - 1);
    }
}
void solve(){
    //cout << Ceil(-13,14) << " " << Floor(-13,14) << endl;
    //return;
    cin >> x >> y >> a >> b;
    if(a > b){
        swap(a, b);
    }
    if(a == b){
        cout << min(x,y)/a << endl;
        return;
    }
    //cout << valid(4) << endl;
    cout << binSearch(0, 1000000000) << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
