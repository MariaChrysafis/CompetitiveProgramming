#include <iostream>
using namespace std;
int query(int l, int r){
    cout << "? " << l << " " << r << endl;
    int ans;
    cin >> ans;
    return ans;
}
void binSearch(int l, int r, int k){
    if(l == r){
        cout << "! " << l << endl;
        return;
    }
    int m = (l + r)/2;
    int ones = query(l, m);
    int zeroes = m - l + 1 - ones;
    if(zeroes >= k){
        int dif = (zeroes - k);
        binSearch(l, m - dif, k);
    }else{
        binSearch(m + 1, r, k - zeroes);
    }
}
int main(){
    int n, t, k;
    cin >> n >> t >> k;
    binSearch(1, n, k);
}
