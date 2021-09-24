class Solution {
    Boolean isSubstring(String s1, String s2) {
        for(int y = 0; y < s2.length(); y++){
            int x1 = 0;
            for(int x2 = y; x2 < s2.length(); x2++) {
                if((char)s2.charAt(x2) == (char)s1.charAt(x1)) {
                    x1++;
                    if(x1 == (int)s1.length()) {
                        return true;
                    }
                } else {
                    x1 = 0;
                }
            }
        }
        return false;
    }
    public int numOfStrings(String[] patterns, String word) {
        int cntr = 0;
        for(String s: patterns) {
            if(isSubstring(s, word)) {
                cntr++;
            }
        }
        return cntr;
    }
}
