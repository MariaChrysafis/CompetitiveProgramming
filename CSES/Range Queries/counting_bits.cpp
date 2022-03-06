#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
 
using namespace std;
vector<int64_t> powr;
int64_t rec (int64_t n) {
    if (__builtin_popcountll(n) == 1) {
        return 1 + n * (log2(n))/2;
    }
    int bt = log2(n);
    //cout << rec(n - powr[bt]) << " " << n - powr[bt] << " " << powr[bt] * bt/2 << '\n';
    return rec(n - powr[bt]) + (n - powr[bt]) + powr[bt] * bt/2 + 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    powr = {1};
    while (powr.size() != 60) {
        powr.push_back(powr.back() * 2);
    }
    int64_t n;
    cin >> n;
    cout << rec(n);
}
