class Solution {
    public String shiftingLetters(String s, int[] shifts) {
        shifts[shifts.length - 1] %= 26;
        for(int i = shifts.length - 2; i >= 0; i--){
            shifts[i] += shifts[i + 1];
            shifts[i] %= 26;
        }
        //System.out.print(map.get('c'));
        StringBuilder ans = new StringBuilder("");
        for(int i = 0; i < s.length(); i++){
            Character c = s.charAt(i);
            for(int j = 0; j < shifts[i]; j++){
                if(c != 'z') c++;
                else c = 'a';
            }
            ans.append(c);
        }
        return ans.toString();
    }
}
