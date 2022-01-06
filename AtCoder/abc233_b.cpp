#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int L, R;
    cin >> L >> R;
    L--, R--;
    string s;
    cin >> s;
    for (int i = L; i < (R + L + 1)/2; i++) {
        swap(s[i], s[R + L - i]);
    }
    cout << s;
}
