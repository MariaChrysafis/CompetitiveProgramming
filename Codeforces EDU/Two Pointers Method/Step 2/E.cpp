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
    if(s == 0) {
        cout << 0;
        return;
    }
    long long l, r;
    l = r = 0;
    long long ans = 0;
    map<long long,long long> myMap;
    myMap[vec[0]]++;
    long long sum = 1;
    while (r != n) {
        if(sum <= s) {
            if(!myMap[vec[r + 1]]) {
                sum++;
            }
            myMap[vec[r + 1]]++;
            r++;
        } else{
            if(myMap[vec[l]] == 1) {
                sum--;
            }
            ans += r - l;
            myMap[vec[l]]--;
            l++;
        }
    }
    ans += (n - l) * (n - l + 1)/2;
    cout <<  ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
