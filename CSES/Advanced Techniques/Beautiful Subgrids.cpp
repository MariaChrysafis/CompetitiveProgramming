#include <iostream>
#include <bitset>
#pragma GCC target("popcnt")
 
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    bitset<3000> arr[n];
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++) {
            if (s[j] == '1') {
                arr[i].set(j);
            }
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = (arr[i] & arr[j]).count();
            ans += x * (x - 1)/2;
        }
    }
    cout << ans;
}
