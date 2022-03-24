#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int64_t> v(N); for (int i = 0; i < N; i++) cin >> v[i];
    int sm = 0;
    for (int i = 0; i < N; i++) {
        if (v[i] == 0) {
            continue;
        }
        int cntr = 1;
        for (int j = i + 1; j < N; j++) {
            if (v[j] == v[i] - cntr) {
                cntr++;
                v[j] = 0;
            }
        }
        v[i] = 0;
        sm++;
    }
    cout << sm;
 
}
