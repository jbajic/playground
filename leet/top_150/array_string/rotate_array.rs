//Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

pub fn rotate(nums: &mut Vec<i32>, k: i32) {
    let mut rotated = nums.clone();

    for i in 0..nums.len() {
        rotated[(i+k as usize) % nums.len()] = nums[i];
    }
    *nums = rotated;
}

// TODO there is another methods of reversing full array, and then each part seperately
// nums = [1,2,3,4,5,6], k = 3
// Full reversal [6,5,4,3,2,1]
// Seperate reversal [4,5,6,1,2,3]

fn main() {
    let mut nums = Vec::from([1,2,3,4,5,6,7]);
    let k = 3;

    rotate(&mut nums, k);
    println!("Rotated: {:?}", nums);
}
