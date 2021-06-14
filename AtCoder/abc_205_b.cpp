#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <stack>
#include <map>
#include <set>
using namespace std;
const int INF = 1000000000;
void print(string s){
    cout << s << endl;
}
int main(){
    int n;
    cin >> n;
    int arr[n];
    set<int> s;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        s.insert(arr[i]);
    }
    if(s.size() != n){
        print("No");
        return 0;
    }
    print("Yes");
}
