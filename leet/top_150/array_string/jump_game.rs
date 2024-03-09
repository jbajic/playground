/*You are given an integer array nums. You are initially positioned at the array's*/
/*first index, and each element in the array represents your maximum jump*/
/*length at that position.*/
/*Return true if you can reach the last index, or false otherwise.*/

use std::collections::HashMap;

pub fn can_jump2(nums: Vec<i32>) -> bool {
    let mut goal = nums.len() - 1;
    for i in (0..nums.len()).rev() {
        if (nums[i] as usize) + i >= goal {
            goal = i;
        }
    }
    
    goal == 0
}

// Too slow
pub fn can_jump(nums: Vec<i32>) -> bool {
    let mut queue = Vec::new();
    queue.push((0, nums[0] as usize));
    let mut dp: HashMap<usize, bool> = HashMap::new();

    while !queue.is_empty() {
        let (index, jump) = queue.pop().unwrap();

        if index == nums.len() -1 {
            return true;
        }

        if jump == 0 {
            dp.insert(index, false);
            continue;
        }

        for i in (index + 1)..(index+1+jump) {
            if !dp.contains_key(&i) && i < nums.len() {
                queue.push((i, nums[i] as usize));
            }
        }
    }

    false
}


fn main() {
    //let nums = Vec::from([2,3,1,1,4]);
    let nums = Vec::from([3,2,1,0,4]);

    println!("Can jump: {}", can_jump2(nums));
}
