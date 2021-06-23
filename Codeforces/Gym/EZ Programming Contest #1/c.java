import java.lang.*;
import java.math.BigInteger;
import java.util.Scanner;
 
public class Main {
    static String convert(Boolean b){
        if(b) return "YES";
        return "NO";
    }
    static Boolean valid(String s){
       return ((s.equals("zepc")) || (s.equals("zpec")) || (s.equals("ezpc")));
    }
    static Boolean solve(String s){
        String str = "";
        for(int j = 0; j < s.length(); j++){
            if(s.charAt(j) == 'e' || s.charAt(j) == 'z' || s.charAt(j) == 'p' || s.charAt(j) == 'c'){
                str += s.charAt(j);
            }
        }
        //System.out.println(valid(str));
        return valid(str);
    }
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        scan.nextLine();
        for(int i = 0; i < t; i++){
            String s = scan.nextLine();
            Boolean b = solve(s);
            System.out.println(convert(b));
        }
    }
}
