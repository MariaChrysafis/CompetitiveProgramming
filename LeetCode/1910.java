class Solution {
    public String removeOccurrences(String s, String part) {
        String str = s.replaceAll(part, "");
        if(str == s) return str;
        else return removeOccurrences(str, part);
    }
}
