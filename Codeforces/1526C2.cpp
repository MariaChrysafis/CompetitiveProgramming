#include <iostream>
#include <queue>
using namespace std;
int main(){
    int n;
    cin >> n;
    priority_queue<int> pq;
    long long pref = 0;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        pq.push(-x), pref += x;
        while(pref < 0){
            pref += pq.top();
            pq.pop();
        }
    }
    cout << pq.size();
}
