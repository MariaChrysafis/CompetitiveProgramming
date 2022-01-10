#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long unsigned ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll K;
    cin >> K;
    vector<ll> powr = {1};
    while (powr.size() != 61) {
        powr.push_back(powr.back() * 2ll);
    }
    string str;
    for (int i = 60; i >= 0; i--) {
        if (powr[i] & K) {
            str += '2';
        } else {
            str += '0';
        }
    }
    reverse(str.begin(), str.end());
    while (str.back() == '0') {
        str.pop_back();
    }
    reverse(str.begin(), str.end());
    cout << str;
}
