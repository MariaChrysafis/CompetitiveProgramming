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
    vector<int> arr(N);
    vector<int> pref = {0};
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    cout << arr[0] << ' ';
    for (int i = 1; i < N; i++) {
        //cout << pref[i]/i;
        cout << (i + 1) * arr[i] - i * arr[i - 1] << " ";
    }
}
