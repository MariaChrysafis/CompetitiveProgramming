#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int res(int a, int b, int x, int y){
    if(x > a || y > b || x <= 0 || y <= 0) return 0;
    int ans = (x - 1) * b;
    ans = max((y - 1) * a, ans);
    return ans;
}
void solve(){
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    x++, y++;
    int ans = 0;
    ans = max(res(a,b,x, y), ans);
    //cout << ans << endl;
    ans = max(ans, res(a, b, a - x + 1, b - y + 1));
    //cout << ans << endl;
    ans = max(ans, res(a, b, a - x + 1, y));
    //cout << ans << " " << a - x + 1 << " " << b << endl;
    ans = max(ans, res(a, b, x, b - y + 1));
    cout << ans << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
