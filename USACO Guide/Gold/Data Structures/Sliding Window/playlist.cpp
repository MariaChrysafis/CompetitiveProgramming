#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int l = 0;
    int r = 0;
    map<int,int> oc;
    oc[arr[l]]++;
    int myMax = 0;
    while (l <= r || l - 1 == r) {
        myMax = max(myMax, r - l + 1);
        if (r == n - 1) {
            break;
        }
        if (oc[arr[r + 1]] == 1) {
            oc[arr[l]]--;
            l++;
            continue;
        }
        oc[arr[r + 1]]++;
        r++;
    }
    cout << myMax;
}
