#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <random>
#include <chrono>
#include <queue>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        long long a, b;
        cin >> a >> b;
        long long ans = -LLONG_MAX;
        for(long long x = min(a,b); x <= min(max(a, b),  min(a,b) + 2); x++){
            long long pos = (b - x)/2 + ((b - x) % 2 == 1);
            pos += (x - a)/2 + ((x - a) % 2 == 1);
            ans = max(ans, pos);
        }
        cout << ans << '\n';
    }

}
