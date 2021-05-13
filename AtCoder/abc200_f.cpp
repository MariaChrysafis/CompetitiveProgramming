#include <iostream>
#include <vector>
#define ll long long
using namespace std;
const long long MOD = 1000000007;
struct modInt{
    long long x;
    modInt operator*(modInt y) const{
        return {(x * y.x) % MOD};
    }
    modInt operator+(modInt y) const{
        return {(x + y.x) % MOD};
    }
};
struct Matrix{
    vector<vector<modInt>> v;
    void print(){
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size(); j++){
                cout << v[i][j].x << " ";
            }
            cout << endl;
        }
    }
    Matrix init(int n, int m){
        Matrix a;
        a.v.resize(n);
        for(int i = 0; i < n; i++) a.v[i].resize(m);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                a.v[i][j].x = 0;
            }
        }
        return a;
    }
    static Matrix identity(int n){
        Matrix m;
        m.v.resize(n);
        for(int i = 0; i < n; i++){
            m.v[i].resize(n);
            for(int j = 0; j < n; j++){
                m.v[i][j].x = 0;
                if(i == j) m.v[i][j].x = 1;
            }
        }
        return m;
    }
    Matrix operator+(const Matrix&m) const{
        Matrix a;
        a.v.resize(m.v.size());
        for(int i = 0; i < m.v.size(); i++){
            for(int j = 0; j < m.v[i].size(); j++){
                a.v[i].push_back(m.v[i][j] + v[i][j]);
            }
        }
        return a;
    }
    Matrix operator*(const Matrix&m) const{
        Matrix ans;
        ans.v.resize(v.size());
        for(int i = 0; i < v.size(); i++) ans.v[i].resize(m.v[0].size());
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < m.v[0].size(); j++){
                for(int k = 0; k < v[0].size(); k++){
                    ans.v[i][j] = ans.v[i][j] + v[i][k] * m.v[k][j];
                }
            }
        }
        return ans;
    }
    Matrix power(long long k){
        Matrix a = (Matrix){v};
        Matrix product = Matrix::identity(a.v.size());
        while(k > 0){
            if(k % 2 == 1){
                product = product * a;
            }
            a = a * a;
            k /= 2;
        }
        return product;
    }
};
Matrix q, zero, one;
Matrix c2m(char c){
    if(c == '0') return zero;
    else if(c == '1') return one;
    return q;
}
int main(){
    string S; int K;
    cin >> S >> K;
    zero = zero.init(5,5), one = zero.init(5,5);
    zero.v[0][0].x = zero.v[1][0].x = zero.v[2][3].x = zero.v[3][3].x = zero.v[2][4].x = zero.v[4][4].x = 1;
    one.v[0][1].x = one.v[1][1].x = one.v[2][2].x = one.v[3][2].x = one.v[0][4].x = one.v[4][4].x = 1;
    q = zero + one;
    Matrix m = Matrix::identity(5);
    for(int i = 1; i < S.size(); i++){
        m = m * c2m(S[i]);
    }
    m = m * (c2m(S[0]) * m).power(K - 1);
    modInt ans; ans.x = 0;
    if(S[0] != '1') ans = ans + m.v[0][4];
    if(S[0] != '0') ans = ans + m.v[2][4];
    //m.print();
    cout << ans.x << endl;
    
}
