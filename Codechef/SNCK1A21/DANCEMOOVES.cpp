#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <climits>
#include <vector>
#include <set>

#define ll int

using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int a, b;
        cin >> a >> b;
        if (a > b) {
            cout << a - b << endl;
            continue;
        } else if (abs(a) % 2 == abs(b) % 2){
            cout << abs(b - a)/2 << endl;
        } else {
            cout << abs(b - a)/2 + 2 << endl;
        }
    }
}
