package com.company;

import java.lang.*;
import java.io.*;
import java.util.*;

public class Main {
    public static class doublyLinkedList<T> {
        Node head, tail;

        static class Node<T> {
            T data;
            Node prev;
            Node next;

            Node(T d) {
                this.data = d;
            }

            void print() {
                System.out.println(data);
            }
        }

        void push_front(T val) {
            Node cur = new Node(val);
            cur.prev = null;
            cur.next = head;
            if (head == null) {
                head = tail = cur;
                return;
            }
            head.prev = cur;
            head = cur;
        }

        void push_back(T val) {
            Node cur = new Node(val);
            cur.prev = tail;
            cur.next = null;
            if (tail == null) {
                head = tail = cur;
                return;
            }
            tail.next = cur;
            tail = cur;
        }

        void pop_back() {
            tail.prev.next = null;
            tail = tail.prev;
        }

        void pop_front() {
            head.next.prev = null;
            head = head.next;
        }

        Node firstOc(T x){
            Node cur = head;
            while(cur.next != null){
                if(cur.data == x){
                    return cur;
                }
                cur = cur.next;
            }
            if(cur.data == x) {
                return cur;
            }
            return null;
        }

        void insertBack(Node cur, T val){
            //if(cur == head || cur == tail) return;
            Node cons = new Node(val);
            cons.prev = cur;
            cons.next = cur.next;
            cur.next = cons;
            if(cur == tail) {
                tail = cons;
            }
        }

        void insertAfterFirstOccurence(T x, T y){
            Node cur = firstOc(x);
            insertBack(cur, y);
        }

        void insertBeforeFirstOccurence(T x, T y) {
            if(head.data == x){
                push_front(y);
                return;
            }
            insertBack(firstOc(x).prev, y);
        }

        void delete_node (Node curNode){
            if(curNode == head){
                pop_front();
                return;
            }
            if(curNode == tail) {
                pop_back();
                return;
            }
            curNode.prev.next = curNode.next;
        }

        void print() {
            Node cur = head;
            while (cur != null) {
                System.out.print(cur.data + "->");
                cur = cur.next;
            }
        }

    }

    public static void main(String[] args) {
        doublyLinkedList<Integer> dll = new doublyLinkedList();
        dll.push_back(8);
        dll.push_front(3);
        dll.push_front(6);
        dll.push_front(10);
        dll.push_back(7);
        dll.pop_front();
        dll.insertAfterFirstOccurence(3, 5);
        dll.insertBeforeFirstOccurence(6, 10);
        dll.delete_node(dll.firstOc(10));
        //dll.firstOc(7).print();
        dll.print();
    }
}
