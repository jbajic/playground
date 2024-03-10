/*Implement the RandomizedSet class:*/
/*RandomizedSet() Initializes the RandomizedSet object.*/
/*bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.*/
/*bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.*/
/*int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element */
/*exists when this method is called). Each element must have the same probability of being returned.*/
/*You must implement the functions of the class such that each function works in average O(1) time complexity.*/


use std::collections::HashMap;

#[derive(Debug)]
struct RandomizedSet {
    map: HashMap<i32, usize>,
    list: Vec<i32>,
}


/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl RandomizedSet {

    fn new() -> Self {
        Self {
            map: HashMap::new(),
            list: Vec::new(),
        }
    }
    
    fn insert(&mut self, val: i32) -> bool {
        if self.map.contains_key(&val) {
            return false;
        }
        self.list.push(val);
        self.map.insert(val, self.list.len()-1);
        true
    }
    
    fn remove(&mut self, val: i32) -> bool {
        if !self.map.contains_key(&val) {
            return false;
        }
        let position = self.map.remove(&val).unwrap();
        let last_elem_in_list = self.list.pop().unwrap();

        // To avoid the removal in the middle of list, we pop the
        // element and put in in place where the one we removed was
        if last_elem_in_list != val {
            self.list[position] = last_elem_in_list.clone();
            self.map.insert(last_elem_in_list, position);
        }
        true
    }
    
    fn get_random(&self) -> i32 {
        return *self.list.first().unwrap();
    }
}


fn main() {
    //Your RandomizedSet object will be instantiated and called as such:
    let mut obj = RandomizedSet::new();

    let val: i32 = 9121;
/*    println!("Insert {:?}", obj.insert(val));*/
    /*println!("Insert {:?}", obj.insert(val));*/

    /*println!("Remove {:?}", obj.remove(val));*/
    /*println!("Remove {:?}", obj.remove(val));*/

    println!("Insert {:?}", obj.insert(-1));
    println!("Remove {:?}", obj.remove(-2));
    println!("Insert {:?}", obj.insert(-2));
    println!("Get {:?}", obj.get_random());
    println!("Remove {:?}", obj.remove(-1));
    println!("Insert {:?}", obj.insert(-2));
    println!("Get {:?}", obj.get_random());
    println!("{:?}", obj);
}
