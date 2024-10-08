class Bank {
public:
    vector<long long> balance;
    Bank(vector<long long>&v) {
        balance.resize(v.size() + 1);
        for (int i = 1; i <= v.size(); i++) {
            balance[i] = v[i - 1];
        }
    }
    
    bool transfer(int account1, int account2, long long money) {
        if (account1 >= balance.size() || account2 >= balance.size()) return false;
        if (balance[account1] - money < 0) return false;
        balance[account2] += money;
        balance[account1] -= money;
        return true;
    }
    
    bool deposit(int account, long long money) {
        if (account >= balance.size()) return false;
        balance[account] += money;
        return true;
    }
    
    bool withdraw(int account, long long money) {
        if (account >= balance.size()) return false;
        if (balance[account] - money < 0) return false;
        balance[account] -= money;
        return true;
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
