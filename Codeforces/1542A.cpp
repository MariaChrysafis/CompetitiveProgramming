#include <iostream>
using namespace std;
void solve(){
    int n;
    cin >> n;
    int o = 0;
    int e = 0;
    n *= 2;
    while(n--){
        int x;
        cin >> x;
        if(x % 2 == 0) o++;
        else e++;
    }
    if(o == e){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
