#include <iostream>
#include <vector>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(2 * n);
    for(int i = 0; i < 2 * n; i++){
        cin >> v[i];
    }
    bool b = true;
    while(b) {
        b = false;
        for (int i = 0; i < 2 * n; i++) {
            int x1 = v[i];
            int x2 = v[(i + 1) % (2 * n)];
            int x3 = v[(i + 2) % (2 * n)];
            if (x1 + x3 == 2 * x2) {
                //cout << x1 << " " << x2 << endl;
                b = true;
                swap(v[i], v[(i + 1) % (2 * n)]);
            }
        }
    }
    print(v);
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
