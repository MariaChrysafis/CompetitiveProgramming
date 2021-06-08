#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int GCD(int a, int b){
    if(min(a,b) == 0) return max(a,b);
    else return GCD(max(a,b) % min(a,b), min(a,b));
}
void print(vector<int> v, int x){
    for(int i = 0; i < v.size() - x; i++){
        cout << v[i] << " ";
    }
    cout << endl;
}
int val(vector<int> v, int n){
    long long ans = 1;
    for(long long i: v){
        ans *= i;
        if(ans > (n * n)) ans %= n;
    }
    return (ans % n);
}
void solve(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        arr[i] = i + 1;
    }
    vector<int> v;
    for(int i = 0; i < n; i++){
        if(GCD(arr[i], n) == 1){
            v.push_back(arr[i]);
        }
    }
    while(val(v, n) != 1){
        v.pop_back();
    }
    cout << v.size() << endl;
    print(v, 0);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
