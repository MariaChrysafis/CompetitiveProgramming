#include <deque>
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        deque<int> stud;
        deque<int> sand;
        for(int i = 0; i < students.size(); i++){
            stud.push_back(students[i]);
            sand.push_back(sandwiches[i]);
        }
        int t = stud.size() * sand.size();
        while(t--){
            if(stud.size() == 0) break;
            if(stud.front() == sand.front()){
                stud.pop_front();
                sand.pop_front();
                continue;
            }else{
                int x = stud[0];
                stud.pop_front();
                stud.push_back(x);
            }
        }
        return stud.size();
    }
};
