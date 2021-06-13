    //package com.MARIAAAA;
    import java.util.*;
    import java.lang.*;
    import java.io.*;
     
    public class Main {
        static void print(int[] arr){
            for(int i = 0; i < arr.length; i++){
                System.out.print(arr[i] );
            }
            System.out.println();
        }
        static boolean isCapital(char c){
            return (c >= 'A' && c <= 'Z');
        }
        static char toUpperCase(char c){
            return Character.toUpperCase(c);
        }
        static char toLowerCase(char c){
            return Character.toLowerCase(c);
        }
        static String transform(String word){
            if(word.length() == 1) return word;
            boolean cap = isCapital(word.charAt(0));
            String str;
            if(cap) str = "" + toUpperCase(word.charAt(word.length() - 1));
            else str = "" + toLowerCase(word.charAt(word.length() - 1));
            for(int i = 1; i < word.length() - 1; i++){
                str = str + word.charAt(word.length() - i - 1);
            }
            str = str + toLowerCase(word.charAt(0));
            return str;
        }
        public static void main(String[] args) throws IOException {
            Scanner sc = new Scanner(System.in);
            String s = sc.nextLine();
            String cur = "";
            Vector<String> v = new Vector<String>(0);
            for(int i = 0; i < s.length(); i++){
                if(s.charAt(i) == ' '){
                    v.add(cur);
                    cur = "";
                }else{
                    cur = cur + s.charAt(i);
                }
            }
            if(cur.length() != 0) v.add(cur);
            for(int i = v.size() - 1; i >= 0; i--){
                System.out.print(transform(v.get(i)) + " ");
            }
        }
    }
