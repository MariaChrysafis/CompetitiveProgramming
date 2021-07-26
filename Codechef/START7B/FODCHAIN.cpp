#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int e, k;
        cin >> e >> k;
        int cntr = 0;
        while(e > 0){
            e /= k;
            cntr++;
        }
        cout << cntr << '\n';
    }

}
