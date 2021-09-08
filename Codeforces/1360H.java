import java.lang.*;
import java.io.*;
import java.util.*;
 
public class Main {
    static class FS {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");
        String next() {
            while(!st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch(Exception e) {}
            }
            return st.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
        long nextLong() {
            return Long.parseLong(next());
        }
    }
    OutputStream outputStream = System.out;
    static final FS sc = new FS();
    static final PrintWriter pw = new PrintWriter(System.out);
    static ArrayList<Long> rem = new ArrayList<>();
    public static int binSearch(long key){
        int l = 0;
        int r = rem.size() - 1;
        int cnt = 0;
        while(l < r){
            int m = (l + r)/2;
            if(rem.get(m) <= key){
                cnt = m + 1;
                l = m + 1;
            }else{
                r = m - 1;
            }
        }
        if(l == r && rem.get(l) <= key){
            return l + 1;
        }
        return cnt;
    }
 
 
    public static String convert(long x, int m){
        ArrayList<Long> arr = new ArrayList<>();
        while(x > 0){
            arr.add(x % 2);
            x /= 2;
        }
        String s = "";
        while(s.length() + arr.size() != m){
            s += '0';
        }
        for(int i = arr.size() - 1; i >= 0; i--){
            if(arr.get(i) == 1){
                s += '1';
            }else{
                s += '0';
            }
        }
        return s;
    }
 
    public static long dif(long mid, long m){
        long left = mid + 1 - binSearch(mid);
        long right = (long)Math.pow(2, m) - left - rem.size() + 1;
        //System.out.println(left + " " + right);
        return left - right;
    }
 
    public static String solve(int m){
        Set<Long> mySet = new HashSet<>();
        for(int i = 0; i < rem.size(); i++){
            mySet.add(rem.get(i));
        }
        long l = 0;
        long r = (long)Math.pow(2, m);
        //System.out.println(dif(3, m));
        //if(3 == 3) return "?";
        while(l <= r) {
            long mid = (l + r + 1) / 2;
            if (mySet.contains(mid)) {
                if ((dif(l, m) == 0 || dif(l, m) == -1) && !mySet.contains(l)) {
                    return convert(l, m);
                }
                l++;
                continue;
            }
            long x = dif(mid, m);
            if (x == 0 || x == -1) {
                return convert(mid, m);
            }
            if (x > 0) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return convert(l, m);
        //return "?";
    }
    public static void main(String[] args) {
        int t = sc.nextInt();
        for(int tc = 0; tc < t; tc++){
            int n = sc.nextInt();
            int m = sc.nextInt();
            rem.clear();
            for(int i = 0; i < n; i++){
                String s = sc.next();
                long ans = 0L;
                long powr = 1L;
                for(int j = 0; j < s.length(); j++){
                    powr *= 2;
                }
                for(int j = 0; j < s.length(); j++){
                    powr /= 2;
                    if(s.charAt(j) == '1'){
                        ans += powr;
                    }
                }
                rem.add(ans);
            }
            for(int j = 0; j < rem.size(); j++){
                for(int k = j + 1; k < rem.size(); k++){
                    if(rem.get(k) < rem.get(j)){
                        long temp = rem.get(k);
                        rem.set(k, rem.get(j));
                        rem.set(j, temp);
                    }
                }
            }
            System.out.println(solve(m));
        }
        pw.close();
    }
}
