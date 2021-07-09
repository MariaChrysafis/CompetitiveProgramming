#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
vector<int> v;
vector<long long> arr;
vector<pair<int,int>> vec;
int n;
bool op(int a){
    int x = (n + (int)log2(a + 1));
    if(x % 2 == 0) return 1;
    else return 0;
}
long long build(int ind){
    if(ind >= v.size() - 1){
        arr[ind] = v[ind - (v.size() - 1)];
        return arr[ind];
    }
    int a = build(2 * ind + 1);
    int b = build(2 * ind + 2);
    if(op(ind)){
        arr[ind] = a ^ b;
    }else{
        arr[ind] = a | b;
    }
    return arr[ind];
}
void update(int k, int u){
    int ind = (v.size() - 1) + k;
    arr[ind] = u;
    while(ind != 0){
        int parent = (ind - 1)/2;
        if(op(parent)){
            arr[parent] = arr[2 * parent + 1] ^ arr[2 * parent + 2];
        }else{
            arr[parent] = arr[2 * parent + 1] | arr[2 * parent + 2];
        }
        ind = parent;
    }
}
int main(){
    int q;
    cin >> n >> q;
    int x = pow(2, n);
    v.resize(x);
    for(int i = 0; i < x; i++){
        cin >> v[i];
    }
    arr.resize(2 * x);
    vec.resize(2 * x);
    build(0);
    while(q--){
        int k,u;
        cin >> k >> u;
        update(k - 1,u);
        cout << arr[0] << endl;
    }
    return 0;
}
