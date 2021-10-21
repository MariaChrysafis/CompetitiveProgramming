#include <iostream>
const int max_x = 1000001;
using namespace std;
int Max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}
int main(){
    int n;
    cin >> n;
    int arr[n];
    int oc[max_x];
    for(int i = 0; i < max_x; i++){
        oc[i] = 0;
    }
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        oc[arr[i]]++;
    }
    int ans = 0;
    for(int i = 1; i < max_x; i++){
        int cntr = 0;
        for(int j = i; j < max_x; j+=i){
            cntr += oc[j];
        }
        if(cntr >= 2) ans = i;
    }
    cout << ans << endl;
}
