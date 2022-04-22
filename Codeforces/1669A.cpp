#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n >= 1900) {
            cout << "Division 1\n";
        } else if (n >= 1600) {
            cout << "Division 2\n";
        } else if (n >= 1400) {
            cout << "Division 3\n";
        } else {
            cout << "Division 4\n";
        }
    }
}
