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
#define MAX_TIME 10001
using namespace std;
int main() {
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);
    int n;
    cin >> n;
    vector<pair<int,int>> vec(n);
    for (int i = 0; i < vec.size(); i++) {
        cin >> vec[i].first >> vec[i].second;
        swap(vec[i].first, vec[i].second);
    }
    sort(vec.begin(), vec.end());
    vector<int> prev(MAX_TIME), cur(MAX_TIME);
    for (int i = 0; i < prev.size(); i++) {
        prev[i] = cur[i] = 0;
    }
    int myMax = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < prev.size(); j++) {
            cur[j] = max(cur[j], prev[j]);
            if (vec[i - 1].first >= j) {
                cur[j] = max(cur[j], prev[j - 1] + vec[i - 1].second);
            }
            myMax = max(myMax, cur[j]);
        }
        prev = cur;
    }
    cout << myMax;
}
