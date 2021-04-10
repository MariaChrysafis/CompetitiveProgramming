#include <iostream>
#include <map>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        map<int,int> myMap;
        int arr[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            myMap[arr[i]]++;
        }
        for(int i = 0; i < n; i++){
            if(myMap[arr[i]] == 1){
                cout << i + 1 << endl;
                break;
            }
        }
    }
}
