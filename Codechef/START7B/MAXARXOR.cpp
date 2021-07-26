#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
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
        long long n, k;
        cin >> n >> k;
        long long powr = (1 << n);
        cout << min((powr - 1) * 2 * k, (powr - 1) * powr) << '\n';
    }

}
