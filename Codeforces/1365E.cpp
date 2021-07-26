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
    int n;
    cin >> n;
    long long v[n];
    long long myMax = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        myMax = max(v[i], myMax);
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            myMax = max(myMax, (v[i] | v[j]));
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            for(int k = j + 1; k < n; k++){
                myMax = max(myMax, (v[i] | v[j]) | v[k]);
            }
        }
    }
    cout << myMax << endl;
}
