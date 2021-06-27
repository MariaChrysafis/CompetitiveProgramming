#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        long long n, a, b;
        cin >> n >> a >> b;
        long long ans = 2 * (180 + n);
        cout << ans - a - b << endl;
    }
}
