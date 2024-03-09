/*You are given a 0-indexed array of integers nums of length n.*/
/*You are initially positioned at nums[0].*/
/*Each element nums[i] represents the maximum length of a forward jump from index i.*/
/*In other words, if you are at nums[i], you can jump to any nums[i + j] where:*/
/*0 <= j <= nums[i] and*/
/*i + j < n*/
/*Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated*/
/*such that you can reach nums[n - 1].*/

use std::collections::HashSet;

pub fn jump2(nums: Vec<i32>) -> i32 {
    let mut jumps = 0;
    let mut window = (0,0);

    while window.1 < nums.len() - 1 {
        let mut max = window.1;
        for i in window.0..window.1+1 {
            max = std::cmp::max(max, i + nums[i] as usize);
        }
        window = (window.1+1,max);
        jumps += 1;
    }

    jumps
}

// Again too slow
pub fn jump(nums: Vec<i32>) -> i32 {
    let mut queue = Vec::new();
    queue.push((0, 0, nums[0] as usize));

    while !queue.is_empty() {
        let (num_jumps, index, jump) = queue.pop().unwrap();
        println!("Current {}, {} with {} jumps", index, jump, num_jumps);

        if index == nums.len() - 1 {
            return num_jumps;
        }

        for i in (index + 1)..(index+1+jump) {
            if i < nums.len() {
                println!("Pushing from {} to {} jumping {}", index, i, num_jumps + 1);
                queue.push((num_jumps + 1, i, nums[i] as usize));
            }
            queue.sort_by(|a, b| b.0.cmp(&a.0));
        }
    }
    0
}

fn main() {
    let nums = Vec::from([2,3,1,1,4]);
    let nums = Vec::from([2,3,0,1,4]);
    let nums = Vec::from([3,2,1]);

    println!("Num of jumps {}", jump2(nums));
}
