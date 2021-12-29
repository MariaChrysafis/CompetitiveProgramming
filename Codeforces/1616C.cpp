#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

typedef int64_t ll;

int gcd (int a, int b) {
    if (!a || !b) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}

pair<int,int> reduce (int a, int b) {
    int g = gcd(abs(a), abs(b));
    a /= g;
    b /= g;
    if ((b < 0 && a > 0) || (a < 0 && b < 0)) {
        b = -b, a = -a;
    }
    return {a, b};
}

pair<int,int> add (pair<int,int> p1, pair<int,int> p2) {
    return reduce(p1.first * p2.second + p1.second * p2.first, p1.second * p2.second);
}

void solve() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            //arr[i] and arr[j] are both in their proper places
            pair<int,int> a = reduce(j * arr[i] - i * arr[j], (j - 1) * i - (i - 1) * j);
            pair<int,int> b = reduce(arr[i] * (j - 1) - arr[j] * (i - 1), j - i);
            pair<int,int> new_arr[n];
            int cnt = 0;
            new_arr[0] = a;
            cnt += (a.second == 1 && a.first == arr[0]);
            pair<int,int> prev = a;
            pair<int,int> addend = add(b, {-a.first, a.second});
            for (int k = 1; k < n; k++) {
                prev = add(prev, addend);
                cnt += (prev.second == 1 && prev.first == arr[k]);
            }
            myMax = max(myMax, cnt);
        }
    }
    cout << n - myMax << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
