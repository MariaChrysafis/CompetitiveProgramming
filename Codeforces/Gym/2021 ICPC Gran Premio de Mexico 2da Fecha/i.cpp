#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

long long rec (long long n) {
    if(n <= 9) {
        return 0;
    }
    string s = to_string(n);
    long long mult = 1;
    for(int i = 0; i < s.length(); i++) {
        mult *= (s[i] - '0');
    }
    //cout << mult << endl;
    return rec(mult) + 1;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        cout << rec(x) << endl;
    }

}
