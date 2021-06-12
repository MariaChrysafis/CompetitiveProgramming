class Solution {
public:
    vector<long long> ch;
    long long K;
    long long one_cycle(){
        long long sum = 0;
        for(long long i: ch) sum += i;
        return sum;
    }
    int chalkReplacer(vector<int>& chalk, int k) {
        ch.resize(chalk.size());
        for(int i = 0; i < chalk.size(); i++) ch[i] = chalk[i];
        K = k;
        //if(one_cycle() == 0)
        K %= one_cycle();
        //cout << one_cycle() << endl;
        while(true){
            for(int i = 0; i < chalk.size(); i++){
                if(K >= ch[i]){
                    K -= ch[i];
                }else{
                    return i;
                }
            }
        }
        return k;
    }
};
