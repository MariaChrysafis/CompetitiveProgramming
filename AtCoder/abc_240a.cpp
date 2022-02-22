#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b;
    cin >> a >> b;
    a--, b--;
    string s = (a % 10 == (b + 1) % 10 || (a + 1) % 10 == b % 10) ? "Yes" : "No";
    cout << s;
}
