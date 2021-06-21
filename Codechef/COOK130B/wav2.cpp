#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
//remember to use '\n'
vector<int> arr;
int binSearch(int l, int r, int x){
    //find first occurence >= x
    if(l == r){
        return l;
    }
    int m = (l + r)/2;
    if(arr[m] < x){
        return binSearch(m + 1, r, x);
    }else{
        return binSearch(l, m, x);
    }
}
int main(){
    int n, q;
    cin >> n >> q;
    set<int> s;
    arr.resize(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        s.insert(arr[i]);
    }
    sort(arr.begin(), arr.end());
    while(q--){
        int query;
        cin >> query;
        if(s.count(query)){
            cout << 0 << '\n';
            continue;
        }
        if(query > arr[n - 1]){
            cout << "POSITIVE" << '\n';
            continue;
        }
        if(query < arr[0]){
            if(n % 2 == 0) cout << "POSITIVE" << '\n';
            else cout << "NEGATIVE" << '\n';
            continue;
        }
        int x = binSearch(0, n - 1, query);
        x += n;
        if(x % 2 == 0) cout << "POSITIVE" << '\n';
        else cout << "NEGATIVE" << '\n';
    }
}
