#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    long long arr[n];
    long long sum = 0;
    long long XOR = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        sum += arr[i];
        XOR ^= arr[i];
    }
    cout << sum - XOR << endl;

}
