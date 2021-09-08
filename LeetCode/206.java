/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode reverseList(ListNode head) {
        if(head == null){
            System.out.println("YES\n");
            return head;
        }
        if(head.next == null){
            return head;
        }
        ListNode cur = head;
        ArrayList<Integer> arr = new ArrayList<>();
        arr.add(cur.val);
        while(cur.next != null){
            cur = cur.next;
            arr.add(cur.val);
        }
        ListNode prev = new ListNode(arr.get(0));
        //if(true == true) return prev;
        cur = new ListNode();
        for(int i = 1; i < arr.size(); i++){
            cur = new ListNode(arr.get(i));
            cur.next = prev;
            prev = cur;
        }
        
        return cur;
        /*
        for(int i = 0; i < arr.size(); i++){
            System.out.print(arr.get(i));
        }
        return head;
        */
    }
}
