#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int arr[n];
    int a[n];
    for(int i = 0; i < n - 1; i++){
        cin >> arr[i];
        a[arr[i]] = -33;
    }
    for(int i = 1; i <= n; i++){
        if(a[i] != -33){
            cout << i << endl;
            return 0;
        }
    }
}
