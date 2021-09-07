#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#define ll long long
using namespace std;
/*
5
1 3
1 5
3
2 2
3

3 5
2 2


 */
int main() {
    int q;
    cin >> q;
    priority_queue<pair<long long, long long>, std::vector<pair<long long, long long>>, greater<>> pq;
    long long suf = 0;
    while (q--){
        int t;
        cin >> t;
        if(t == 1) {
            long long x;
            cin >> x;
            pq.push({x - suf, suf});
        } else if(t == 2) {
            long long x;
            cin >> x;
            suf += x;
        } else if (t == 3) {
            // find ball of smallest value
            cout << pq.top().first + suf << endl;
            pq.pop();
        }
    }
}
