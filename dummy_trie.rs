use std::vec;
use std::cmp::max;
use std::cmp::min;
use std::collections::vec_deque::VecDeque;
use std::io::{self, BufRead};
use std::mem;
#[derive(Default, Debug)]
struct Trie {
    children: [Option<Box<Trie>>; 2],
    sz: usize,
}
impl Trie {
    fn new () -> Trie {
        Default::default()
    }
    pub fn add (&mut self, x: i32) {
        let mut cur = self;
        for i in 0..30 {
            let val: usize = min(x & (1 << i), 1) as usize;
            if cur.children[val].is_none() {
                cur.children[val] = Some(Box::new(Trie::new()));
            }
            cur.sz += 1;
            cur = cur.children[val].as_mut().unwrap();
        }
    }

    pub fn search (&mut self, x: i32) -> bool {
        let mut cur = self;
        for i in 0..30 {
            let val: usize = min(x & (1 << i), 1) as usize;
            if cur.children[val].is_none() {
                return false;
            }
            cur = cur.children[val].as_mut().unwrap();
        }
        return true;
    }
}

fn main() {
    let mut trie = Trie::new();
    trie.add(50001);
    trie.add(50002);
    println!("{}", trie.search(5001));
}
