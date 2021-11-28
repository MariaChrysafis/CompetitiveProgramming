class Solution {
public:
    int minimumBuckets(string street) {
        cout << street << endl;
        for (int i = 1; i < street.length() - 1; i++) {
            if (street[i] == 'H' && street[i + 1] == 'H' && street[i - 1] == 'H') {
                return -1;
            }
        }
        if (street.length() >= 2 && street[0] == 'H' && street[1] == 'H') {
            return -1;
        }
        if (street.length() >= 2 && street[street.length() - 1] == 'H' && street[street.length() - 2] == 'H') {
            return -1;
        }
        if (street.length() == 1) {
            if (street[0] == 'H') return -1;
            return 0;
        }
        for (int i = 0; i < street.length() - 2; i++) {
            if (street[i] == 'H' && street[i + 1] == '.' && street[i + 2] == 'H') {
                street[i + 1] = 'R';
                street[i] = street[i + 2] = '.';
            }
        }
        int ans = 0;
        for (char c: street) {
            ans += (c == 'R' || c == 'H');
        }
        cout << street << endl;
        return ans;
    }
};
