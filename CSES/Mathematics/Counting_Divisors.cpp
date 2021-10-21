#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#define ll int
 
using namespace std;
int main() {
    vector<int> primeFactor((int)1e6 + 1);
    vector<int> div((int)1e6 + 1);
    for (int i = 0; i < primeFactor.size(); i++) {
        primeFactor[i] = div[i] = i;
    }
    for (int i = 2; i < primeFactor.size(); i++) {
        if (primeFactor[i] == i) {
            for (int j = 2 * i; j < primeFactor.size(); j += i) {
                primeFactor[j] = i;
            }
        }
    }
    for (int i = 2; i < div.size(); i++) {
        if (primeFactor[i] == i) {
            div[i] = 2;
        } else {
            int dum = i;
            int cntr = 1;
            while (dum % primeFactor[i] == 0) {
                dum /= primeFactor[i];
                cntr++;
            }
            div[i] = div[dum] * cntr;
        }
    }
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        cout << div[n] << endl;
    }
}
