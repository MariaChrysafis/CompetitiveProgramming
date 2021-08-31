#include <iostream>
#include <vector>
#define ll long long
using namespace std;
int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; i++){
        cin >> v[i];
        if (i % 2 == 1){
            v[i] = -v[i];
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++){
        if (v[i] < 0) {
            continue;
        }
        long long pref = 0;
        long long myMin = 1e9;
        for (int j = i + 1; j < n; j++){
            if (j != i + 1) {
                pref += v[j - 1];
                myMin = min(myMin, pref);
            }
            if (v[j] > 0) {
                continue;
            }
            ans += max(min(v[i], - pref - v[j]) - max(1ll, -myMin) + 1, 0ll);
        }
    }
    cout << ans << endl;
}
