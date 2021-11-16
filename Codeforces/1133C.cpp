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
vector<int> v;
int binSearch (int l, int r, int k) {
    //find the last thing that is <= k
    if (l == r) {
        return l;
    }
    int m = (l + r + 1)/2;
    if (v[m] <= k) {
        return binSearch(m, r, k);
    }
    return binSearch(l, m - 1, k);
}
int main() {
    int n;
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int myMax = 0;
    for (int i = 0; i < v.size(); i++) {
        int x = binSearch(i, (int)v.size() - 1, v[i] + 5);
        //cout << x - i + 1 << endl;
        myMax = max(myMax, x - i + 1);
    }
    cout << myMax;
}
