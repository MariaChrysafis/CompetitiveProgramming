#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
const int maxN = 301;
double dp[maxN][maxN][maxN];
int numOnes = 0;
int numTwos = 0;
int numThrees = 0;
int N;
double expected(int ones, int twos, int threes){
    if(ones < 0 || twos < 0 || threes < 0){
        return 0;
    }
    if(dp[ones][twos][threes] != -1){
        return dp[ones][twos][threes];
    }
    double k = ones + twos + threes;
    //we pick a zero
    double c0 = N;
    //we pick a one
    double c1 = ones * expected(ones - 1, twos, threes);
    //we pick a two
    double c2 = twos * expected(ones + 1, twos - 1, threes);
    //we pick a three
    double c3 = threes * expected(ones, twos + 1, threes - 1);
    dp[ones][twos][threes] = (c1 + c2 + c3 + c0)/k;
    return dp[ones][twos][threes];
}
int main(){
    for(int i = 0; i < maxN; i++){
        for(int j = 0; j < maxN; j++){
            for(int k = 0; k < maxN; k++){
                dp[i][j][k] = -1.0;
            }
        }
    }
    cin >> N;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        if (a == 1) numOnes++;
        if (a == 2) numTwos++;
        if (a == 3) numThrees++;
    }
    dp[0][0][0] = 0;
    cout << setprecision(20) << expected(numOnes, numTwos, numThrees);
}
