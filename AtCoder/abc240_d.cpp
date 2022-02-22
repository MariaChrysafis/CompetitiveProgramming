#include <cmath>
#include <cassert>
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
#include <stack>

using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> a;
    vector<pair<int,int>> rem;
    int cnt = 0;
    int prev = -1;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        a.push_back(x);
        if (x != prev) {
            if (prev != -1) {
                rem.emplace_back(prev, cnt);
            }
            prev = x;
            cnt = 1;
        } else {
            cnt++;
        }
        if (cnt == prev) {
            while (cnt--) {
                a.pop_back();
            }
            if (rem.empty()) {
                assert(a.empty());
                prev = -1;
            } else {
                prev = rem.back().first;
                cnt = rem.back().second;
                rem.pop_back();
            }
        }
        cout << a.size() << '\n';
    }
}
