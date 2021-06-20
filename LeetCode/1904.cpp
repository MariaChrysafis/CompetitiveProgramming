class Solution {
public:
    int to_int(char c){
        return c - '0';
    }
    int to_int(string s){
        return 10 * to_int(s[0]) + to_int(s[1]);
    }
    int to_int(char c1, char c2){
        return 10 * to_int(c1) + to_int(c2);
    }
    int ans(int time1, int time2){
        if(time1 > time2){
            time2 += 1440;
        }
        //cout << time1 << " " << time2 << endl;
        int cntr = 0;
        for(int i = time1; i <= time2; i++){
            //cout << i << endl;
            int strt = i;
            int end = i + 15;
            if(i % 15 == 0 && end <= time2){
                cntr++;
            }
        }
        return cntr;
    }
    int numberOfRounds(string startTime, string finishTime) {
        //cout << to_int('1', '2') << endl;
        int time1 = to_int(startTime[0], startTime[1]) * 60 + to_int(startTime[3], startTime[4]);
        int time2 = to_int(finishTime[0], finishTime[1]) * 60 + to_int(finishTime[3], finishTime[4]);
        //cout << to_int(startTime[2], startTime[3]) << endl;
        cout << time1 << " " << time2 << endl;
        return ans(time1, time2);
    }
};
