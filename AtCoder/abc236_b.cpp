#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> oc;
    oc.assign(n, 0);
    int arr[4 * n - 1];
    for (int i = 0; i < 4 * n - 1; i++) {
        cin >> arr[i];
        oc[arr[i] - 1]++;
    }
    for (int i = 0; i < n; i++) {
        if (oc[i] != 4) {
            cout << i + 1;
        }
    }
}
