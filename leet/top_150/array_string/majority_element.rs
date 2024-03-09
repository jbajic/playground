/*Given an array nums of size n, return the majority element.*/
/*The majority element is the element that appears more than ⌊n / 2⌋ times.*/
/*You may assume that the majority element always exists in the array.*/


pub fn majority_element(nums: Vec<i32>) -> i32 {
    let mut count = 1;
    let mut max = nums[0];

    for i in 1..nums.len() {
    if nums[i] == max {
            count += 1;
        } else {
            count -= 1;
            if count == 0 {
                max = nums[i];
                count = 1;
            }
        }
    }

    max
}

fn main() {
    let nums = Vec::from([2,2,1,1,1,2,2]);
    println!("Majority elem is {}", majority_element(nums));
}
