#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
 
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    map<int,int> myMap;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        myMap[a[i]] = i + 1;
        a[i] = i + 1;
    }
    map<int,int> index;
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        b[i] = myMap[b[i]];
        index[b[i]] = i;
    }
    int cur = 0;
    int cntr = 0;
    for(int i = 1; i <= n; i++){
        if(index[i] >= cur){
            cur = index[i];
            cntr++;
        }
    }
    cout << n - cntr << endl;
}
