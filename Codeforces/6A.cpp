#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> vec(4);
    cin >> vec[0] >> vec[1] >> vec[2] >> vec[3];
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        for (int j = i + 1; j < vec.size(); j++) {
            for (int k = j + 1; k < vec.size(); k++) {
                if (vec[k] < vec[i] + vec[j]) {
                    cout << "TRIANGLE\n";
                    return 0;
                }
            }
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        for (int j = i + 1; j < vec.size(); j++) {
            for (int k = j + 1; k < vec.size(); k++) {
                if (vec[k] == vec[i] + vec[j]) {
                    cout << "SEGMENT\n";
                    return 0;
                }
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}
