import java.util.*;
import java.lang.*;
import java.io.*;
import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        for(int tc = 0; tc < t; tc++){
            int n = scan.nextInt();
            int m = scan.nextInt();
            int x = scan.nextInt();
            int y = scan.nextInt();
            //continue;
 
            String[] arr = new String[n];
            for(int i = 0; i < n; i++) arr[i] = scan.next();
            int two = 0;
            int one = 0;
            for(int i = 0; i < n; i++){
                int cur = 0;
                for(int j = 0; j < m; j++){
                    if(cur == 1 && arr[i].charAt(j) == '.'){
                        cur = 0;
                        two++;
                        one++;
                    }else if (arr[i].charAt(j) == '.'){
                        cur = 1;
                        one++;
                    }else{
                        cur = 0;
                    }
                }
            }
            one -= 2 * two;
            //System.out.println(one + " " + two);
            if(2 * x <= y){
                System.out.println((one + 2 * two) * x);
            }else{
                System.out.println(two * y + one * x);
            }
        }
    }
 
}
