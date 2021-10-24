#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    set<int> s = {0};
    for (int i = 0; i < n; i++) {
        set<int> prev = s;
        for (int val: prev) {
            s.insert(val + arr[i]);
        }
    }
    s.erase(0);
    cout << s.size() << endl;
    for (int i: s) {
        cout << i << " ";
    }
}
