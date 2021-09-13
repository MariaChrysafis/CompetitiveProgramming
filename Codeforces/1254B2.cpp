#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
template <typename T>
T readVal(){
    T n;
    cin >> n;
    return n;
}
template <typename T>
vector<T> readVector(T n){
    vector<T> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}
template <typename T>
void printVector(vector<T> vec){
    for(T x: vec){
        cout << x << " ";
    }
    cout << endl;
}
long long solver(vector<long long> vec, long long prime){
    for(int i = 0; i < vec.size(); i++){
        vec[i] %= prime;
    }
    long long cntr = 0;
    for(int i = 0; i < vec.size(); i++){
        long long delta1 = prime - vec[i]; //or add prime - vec[i]
        long long delta2 = -vec[i]; //remove vec[i]
        if(vec[i] == 0) {
            continue;
        }
        if (abs(delta2) < abs(delta1)){
           vec[i] += delta2;
           vec[i + 1] -= delta2;
           vec[i + 1] = (vec[i + 1] + prime) % prime;
           cntr += abs(delta2);
        } else {
            vec[i] += delta1;
            vec[i + 1] -= delta1;
            vec[i + 1] = (vec[i + 1] + prime) % prime;
            cntr += abs(delta1);
        }
    }
    return cntr;
}
void solve() {
    int n = readVal<int>();
    vector<long long> v = readVector<long long>(n);
    long long sum = 0;
    for(long long i: v){
        sum += i; 
    }
    vector<long long> primes;
    for(long long i = 2; i <= sqrt(sum); i++){
        if(sum % i == 0){
            while(sum % i == 0){
                sum /= i;
            }
            primes.push_back(i);
        }
    }
    if(sum != 1) {
        primes.push_back(sum);
    }
    if(primes.size() == 0){
        cout << -1 << endl;
        return;
    }
    long long myMin = LLONG_MAX;
    for(long long i: primes) {myMin = min(myMin, solver(v, i));
    }
    cout << myMin;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
