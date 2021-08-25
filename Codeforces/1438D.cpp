#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int find_index(vector<int> v, int val){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == val){
            return i;
        }
    }
    return -1;
}
vector<int> reverse(vector<int> v, int pref){
    cout << pref + 1 << " ";
    reverse(v.begin(), v.begin() + pref + 1);
    return v;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    int bitXor = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        bitXor ^= v[i];
    }
    if(n == 3){
        cout << "YES\n";
        cout << "1 \n1 2 3\n";
        return;
    }
    if(n % 2 == 0 && bitXor != 0){
        cout << "NO\n";
        return;
    }
    if(n % 2 == 0) n--;
    int last = 3;
    cout << "YES\n";
    cout << n - 2 << endl;
    cout << "1 2 3 \n";
    while(true){
        if(last + 2 <= n) cout << last << " " << last + 1 << " " << last + 2 << '\n';
        else break;
        last += 2;
    }
    if(n != 3) cout << n - 4 << " " << n - 3 << " " << n - 2 << endl;
    last = n - 4;
    while(true){
        if(last - 2 >= 1) cout << last << " " << last - 1 << " " << last - 2 << endl;
        else break;
        last -= 2;
    }
}
int main(){
    solve();
}
