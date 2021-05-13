#include <iostream>
#include <iomanip>
using namespace std;
int main(){
    int n;
    cin >> n;
    long long arr[n];
    long long mod[200];
    for(int i = 0; i < 200; i++) mod[i] = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        mod[arr[i] % 200]++;
    }
    long long cntr = 0;
    for(int i = 0; i < 200; i++){
        cntr += mod[i] * (mod[i] - 1)/2;
    }
    cout << setprecision(20) << cntr << endl;
}
