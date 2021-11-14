#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <regex>
using namespace std;
//vector<long long> arr = {1, 3, 2, 5, 4};
long long query (long long l, long long r) {
    /*
    long long cntr = 0;
    vector<int> v;
    for (int i = l; i <= r; i++) {
        v.push_back(arr[i]);
    }
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < i; j++) {
            if (v[j] > v[i]) {
                cntr++;
            }
        }
    }
    return cntr;
     */
    cout << "? " << l + 1 << " " << r + 1 << '\n';
    cout.flush();
    long long x;
    cin >> x;
    return x;
}
long long n;
long long binSearch (long long l, long long r) {
    long long m = (l + r + 1)/2;
    long long left = query(0, m);
    if (l == r) {
        return l;
    }
    if (left == 0) {
        return binSearch(m, r);
    } else {
        return binSearch(l, m - 1);
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        int p = binSearch(0, n - 1);
        int len = query(p, n - 1) - query(p + 1, n - 1);;
        int j = p + len + 1;
        int len1 = query(j, n - 1) - query(j + 1, n - 1);
        cout << "! " << 1 + p << " " << p + len + 2 << " " << j + len1 + 1 << '\n';
    }
}
