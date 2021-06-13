 By Olympia02:18, contest: mBIT Standard Spring 2021, problem: (E) Pokémon Permutation, Perfect result: 40 points, #, Copy

    import java.util.*;
    import java.lang.*;
    import java.io.*;
     
    public class Main {
        static int GCD(int a, int b){
            if(Math.min(a,b) == 0) return Math.max(a,b);
            return GCD(Math.max(a,b) % Math.min(a,b), Math.min(a,b));
        }
        public static void main(String[] args) throws IOException {
            Scanner sc = new Scanner(System.in);
            String s = sc.nextLine();
            Map<Character,Integer> myMap = new HashMap<Character,Integer>();
            for(Character c = 'a'; c != '?'; c++){
                myMap.put(c, 0);
                if(c == 'z') break;
            }
            for(int i = 0; i < s.length(); i++){
                char c = s.charAt(i);
                int x = myMap.get(c);
                //System.out.println("YES");
                myMap.put(c, x + 1);
            }
     
            Vector<Character> vc = new Vector<Character>(0);
            Vector<Integer> vi = new Vector<Integer>(0);
            for(Map.Entry<Character, Integer> me: myMap.entrySet()){
                if(me.getValue() == 0) continue;
                vi.add(me.getValue());
                vc.add(me.getKey());
            }
            int gcd = 0;
            for(int i = 0; i < vc.size(); i++){
                gcd = GCD(gcd, vi.get(i));
     
            }
            //System.out.println(gcd);
            if(gcd == 1){
                System.out.println("IMPOSSIBLE");
                return;
            }
            String base = "";
            for(int i = 0; i < vi.size(); i++){
                int x = vi.get(i)/gcd;
                for(int j = 0; j < x; j++){
                    char c = vc.get(i).charValue();
                    base = base + c;
                }
            }
            //String ans = "";
            for(int i = 0; i < gcd; i++){
                System.out.print(base);
            }
            //System.out.println(ans);
        }
    }
             

