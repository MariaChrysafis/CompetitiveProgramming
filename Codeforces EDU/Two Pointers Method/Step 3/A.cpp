#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

pair<long long,long long> solver(vector<long long> vec, long long s) {
    long long n = vec.size();
    for(long long i = 0; i < 6 * n; i++) {
        vec.push_back(vec[i]);
    }
    n = vec.size();
    long long l, r;
    l = r = 0;
    long long sum = vec[0];
    long long myMin = 1e18 + 1;
    long long starting = 0;
    while (r != n) {
        if(sum < s) {
            sum += vec[r + 1];
            r++;
        } else {
            if (r - l + 1 < myMin) {
                myMin = r - l + 1;
                starting = l;
            }
            sum -= vec[l];
            l++;
        }
    }
    return {starting + 1, myMin};
}

void solve () {
    long long n;
    long long s;
    cin >> n >> s;
    vector<long long> vec(n);
    for(int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    pair<long long,long long> p = solver(vec, s);
    if(p.second != 1e18 + 1) {
        cout << p.first << " " << p.second;
        return;
    }
    long long sum = 0;
    for(long long i = 0; i < n; i++) {
        sum += vec[i];
    }
    long long delta = s/sum - 2;
    s -= sum * (s/sum - 2);
    p = solver(vec, s);
    cout << p.first << " " << p.second + delta * n << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
