#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

long long delta (long long a, long long b, long long ab, char c) {
    //add a character c to the end
    if(c == 'b') {
        ab += a;
    }
    return ab;
}

void solve () {
    long long n, c;
    cin >> n >> c;
    string s;
    cin >> s;
    long long l = 0;
    long long r = 0;
    long long a = (s[0] == 'a');
    long long b = (s[0] == 'b');
    long long ab = 0;
    long long myMax = 0;
    while (r != n - 1) {
        if(delta(a, b, ab, s[r + 1]) <= c) {
            r++;
            if(s[r] == 'b') b++, ab += a;
            else if(s[r] == 'a') a++;
        } else {
            myMax = max(myMax, r - l + 1);
            if(s[l] == 'a') ab -= b, a--;
            else if(s[l] == 'b') b--;
            l++;
        }
    }
    myMax = max(myMax, n - l);
    cout << myMax << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
