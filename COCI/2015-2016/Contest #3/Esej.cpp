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
    srand(time(NULL));
    int A, B;
    cin >> A >> B;
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < 15; j++) {
            int x = (int)rand() % 26;
            cout << (char)('a' + x);
        }
        cout << ' ';
    }
}
