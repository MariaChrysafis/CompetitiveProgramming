#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int N;
vector<vector<double>> p;
vector<double> head;
double prob(int tot, int heads){
    if(heads > tot || tot < 0 || heads < 0) return 0;
    if(p[tot][heads] != -1){
        return p[tot][heads];
    }
    p[tot][heads] = prob(tot - 1, heads - 1) * head[tot - 1] + prob(tot - 1, heads) * (1 - head[tot - 1]);
    return p[tot][heads];
}
int main(){
    cin >> N;
    p.resize(N + 1);
    head.resize(N);
    for(int i = 0; i <= N; i++){
        if(i != N) cin >> head[i];
        p[i].resize(N + 1);
        for(int j = 0; j <= N; j++){
            p[i][j] = -1;
        }
    }
    p[1][1] = head[0];
    p[1][0] = 1 - head[0];
    double ans = 0;
    for(int i = (N + 1)/2; i <= N; i++){
        ans += prob(N, i);
    }
    cout << setprecision(10)  << ans << endl;
}
