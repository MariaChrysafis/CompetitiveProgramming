#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cassert>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> d(n);
    vector<int> myMap;
    myMap.assign(k, 0);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        d[i] %= k;
        myMap[d[i]]++;
    }
    //cout << myMap[0] << endl;
    int ans = 0;
    for (int i = 0; i <= k/2; i++) {
        if (i * 2 != k && i != 0) ans += 2 * min(myMap[i], myMap[k - i]);
        else ans += myMap[i]/2 * 2;
    }
    cout << ans;
}
