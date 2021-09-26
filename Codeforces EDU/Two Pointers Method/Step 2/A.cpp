#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;
void solve () {
    long long n;
    long long s;
    cin >> n >> s;
    vector<long long> vec;
    for(int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        vec.push_back(x);
    }
    if(vec.empty()) {
        cout << 0;
        return;
    }
    long long l = 0;
    long long sum = 0;
    long long myMax = 0;
    for (int r = 0; r < vec.size(); r++) {
        sum += vec[r];
        while (sum > s) {
            sum -= vec[l];
            l++;
        }
        myMax = max(myMax, r - l + 1);
    }
    cout << myMax;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
