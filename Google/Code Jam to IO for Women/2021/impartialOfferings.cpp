#include <iostream>
#include <algorithm>
using namespace std;
int solve(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    sort(arr, arr + n);
    int cntr = 0;
    int x = 1;
    for(int i = 0; i < n; i++){
        if(i == 0){
        	//cout << x << " ";
            cntr += x;
            continue;
        }
        if(arr[i] == arr[i - 1]){
        	//cout << x << " ";
            cntr += x;
            continue;
        }else{
            x++;
            //cout << x << " ";
            cntr +=x;
        }
    }
    //cout << endl;
    return cntr;
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
    	cout << "Case #" << i + 1 << ": ";
        int x = solve();
        cout << x << endl;
    }
}
