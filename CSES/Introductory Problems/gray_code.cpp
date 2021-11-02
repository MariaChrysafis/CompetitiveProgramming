#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
#include <iomanip>
#define ll unsigned long long
using namespace std;
int dist (pair<int,int> p1, pair<int,int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<string> v[n + 1];
    v[0] = {"0", "1"};
    for (int i = 1; i <= n; i++) {
        vector<string> v1 = v[i - 1];
        vector<string> v2 = v[i - 1];
        reverse(v2.begin(), v2.end());
        vector<string> vec;
        for (int j = 0; j < v1.size(); j++) {
            vec.push_back('0' + v1[j]);
        }
        for (int j = 0; j < v1.size(); j++) {
            vec.push_back('1' + v2[j]);
        }
        v[i] = vec;
    }
    for (string s: v[n - 1]) {
        cout << s << endl;
    }
}
