#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> odd;
    vector<int> even;
    if(n == 2){
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    if(n == 1){
        cout << 1 << endl;
        return 0;
    }
    if(n == 3){
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    if(n == 4){
        cout << "3 1 4 2" << endl;
        return 0;
    }
    for(int i = 0; i < n; i++){
        if(i % 2 == 0) odd.push_back(i + 1);
        if(i % 2 == 1) even.push_back(i + 1);
    }
    for(int i: odd) cout << i << " ";
    for(int i: even) cout << i << " ";
}
 
