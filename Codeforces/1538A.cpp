#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int find_ind(vector<int> v, int x){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == x) return i;
    }
}
int best(int n, int ind){
    return min(ind + 1, n - ind);
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    int myMin = 1e9;
    int myMax = 0;
    for(int i: v) myMin = min(myMin, i), myMax = max(myMax, i);
        //cout << myMin << " " << myMax << endl;
    int ind1 = find_ind(v, myMin);
    int ind2 = find_ind(v, myMax);
    int pos1 = min(ind1 + 1, n - ind1) + min(ind2 + 1, n - ind2);
    int pos2 = n - min(ind1, ind2);
    int pos3 = max(ind1, ind2) + 1;
    //cout << ind1 << " " << ind2 << endl;
    //cout << pos1 << " " << pos2 << " " << pos3 << endl;
    cout << min(min(pos1, pos2), pos3) << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while(q--){
        solve();
    }
}
