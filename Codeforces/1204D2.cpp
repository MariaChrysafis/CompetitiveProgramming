#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
int main() {
    string s;
    cin >> s;
    vector<pair<char,int>> q;
    for (int i = 0; i < s.length(); i++) {
        q.push_back(make_pair(s[i], i));
        while (q.size() >= 2 && q[q.size() - 2].first == '1' && q[q.size() - 1].first == '0') {
            q.pop_back();
            q.pop_back();
        }
    }
    for (auto p: q) {
        s[p.second] = '0';
    }
    cout << s;
}
