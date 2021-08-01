class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        sort(milestones.begin(), milestones.end());
        long long sum = 0;
        for(int i = 0; i < milestones.size(); i++){
            sum += milestones[i];
        }
        if(milestones.back() * 2 <= sum){
            return sum;
        }
        return (sum - milestones.back()) * 2 + 1;
    }
};
