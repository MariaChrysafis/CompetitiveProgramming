class Solution {
public:
    bool isPrime(int n){
        for(int i = 2; i <= sqrt(n); i++){
            if(n % i == 0){
                return false;
            }
        }
        return true;
    }
    bool isThree(int n) {
        if(n == 1){
            return false;
        }
        return (int(sqrt(n)) * (int)(sqrt(n)) == n && isPrime((int)sqrt(n)));
    }
};
