#include <iostream>
using namespace std;
string yes = "Yes";
string no = "No";
const int MAX = 1000000000;
string solve(){
    int x;
    cin >> x;
    int a, b;
    cin >> a >> b;
    if(x % b == 1){
        return yes;
    }
    long long cur = 1;
    for(int powr = 1; powr < 100; powr++){
        cur *= a;
        if(cur > MAX){
            break;
        }
        if(cur % b == x % b && cur <= x){
            return yes;
        }
    }
    return no;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        cout << solve() << "\n";
    }
}
