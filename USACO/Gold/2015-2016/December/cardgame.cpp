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
int biggerWins (vector<int> elsie, vector<int> bessie) {
    sort(bessie.begin(), bessie.end());
    sort(elsie.begin(), elsie.end());
    int l = 0;
    int r = 0;
    int cntr = 0;
    while (l != elsie.size() && r != elsie.size()) {
        if (bessie[r] > elsie[l]) {
            r++, l++;
            cntr++;
        } else {
            r++;
        }
    }
    return cntr;
}
vector<int> split (vector<int> v, int l, int r) {
    vector<int> vec;
    for (int i = l; i <= r; i++) {
        vec.push_back(v[i]);
    }
    return vec;
}
vector<int> negatevec (vector<int> v) {
    vector<int> vec;
    for (int i = 0; i < v.size(); i++) {
        vec.push_back(-v[i]);
    }
    return vec;
}
int main() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> elsie(n), bessie;
    bool used[2 * n + 1];
    for (int i = 0; i <= 2 * n + 1; i++) {
        used[i] = false;
    }
    for (int i = 0; i < n; i++) {
        cin >> elsie[i];
        used[elsie[i]] = true;
    }
    for (int i = 1; i <= 2 * n + 1; i++) {
        if (!used[i]) {
            bessie.push_back(i);
        }
    }
    sort(bessie.begin(), bessie.end());
    int ans = 0;
    ans += biggerWins(split(elsie, 0, n/2 - 1), split(bessie, n/2, n - 1));
    ans += biggerWins(negatevec(split(elsie, n / 2, n - 1)), negatevec(split(bessie, 0, n / 2 - 1)));
    cout << ans;
}
