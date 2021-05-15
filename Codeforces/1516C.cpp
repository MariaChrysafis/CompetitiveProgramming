#include <iostream>
#include <cmath>
#include <set>
#include <vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    //set<int> s;
    int arr[n];
    int sum = 0;
    for(int i = 0; i < n; i++){ cin >> arr[i]; sum += arr[i]; }
    set<int> s;
    s.insert(0);
    for(int i = 0; i < n; i++){
        //s.insert(arr[i]);
        vector<int> v;
        for(auto it = s.begin(); it != s.end(); it++){
            v.push_back(*it + arr[i]);
        }
        for(int i: v) s.insert(i);
    }
    if(!s.count(sum/2) || sum % 2 == 1){
        cout << 0 << endl;
        return 0;
    }
    for(int j = 1; j < 13; j++){
        for(int i = 0; i < n; i++){
            int pwr = pow(2,j);
            if(arr[i] % pwr != 0){
                cout << 1 << endl;
                cout << i + 1 << endl;
                return 0;
            }
        }
    }
}
