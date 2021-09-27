#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void solve () {
    long long n, m, s, A, B;
    cin >> n >> m >> s >> A >> B;
    vector<long long> a(n), b(m);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<long long> prefA = {0};
    vector<long long> prefB = {0};
    for(int i = 0; i < n; i++) prefA.push_back(prefA.back() + a[i]);
    for(int i = 0; i < m; i++) prefB.push_back(prefB.back() + b[i]);
    long long myMax = 0;
    for(int i = 0; i <= n; i++) {
        if(A * i > s) {
            break;
        }
        long long j = min((s - A * i)/B, m);
        myMax = max(myMax, prefA[i] + prefB[j]);
    }
    cout << myMax << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
