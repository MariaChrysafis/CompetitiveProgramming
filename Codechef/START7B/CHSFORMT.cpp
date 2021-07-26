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
        int a, b;
        cin >> a >> b;
        if(a + b < 3) cout << 1;
        else if(a + b <= 10) cout << 2;
        else if(a + b <= 60) cout << 3;
        else cout << 4;
        cout << '\n';
    }

}
