#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#define ll long long
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(m);
    for(int i = 0; i < n; i++) cin >> A[i];
    for(int i = 0; i < m; i++) cin >> B[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    int ind1 = 0;
    int ind2 = 0;
    int myMin = 1e9;
    while(ind1 < n && ind2 < m){
        myMin = min(myMin, abs(A[ind1] - B[ind2]));
        if(myMin == 0) break;
        if(ind1 == n - 1 && ind2 == m - 1){
            break;
        }
        if(ind1 == n - 1){
            ind2++;
            continue;
        }
        if(ind2 == m - 1){
            ind1++;
            continue;
        }
        if(A[ind1] < B[ind2]){
            ind1++;
            continue;
        }
        if(A[ind1] > B[ind2]){
            ind2++;
        }
    }
    cout << myMin << endl;
}
