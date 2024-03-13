/*Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order,*/
/*find two numbers such that they add up to a specific target number. Let these two numbers */
/*be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.*/
/*Return the indices of the two numbers, index1 and index2, added by one as an integer*/
/*array [index1, index2] of length 2.*/
/*The tests are generated such that there is exactly one solution. You may not use the same*/
/*element twice.*/
/*Your solution must use only constant extra space.*/

pub fn two_sum(numbers: Vec<i32>, target: i32) -> Vec<i32> {
    let mut left_i = 0;
    let mut right_i = numbers.len() - 1;
/*    while numbers[right_i] >= target {*/
        /*right_i -= 1;*/
    /*}*/
    
    while left_i < right_i {
        let sum = numbers[left_i] + numbers[right_i];
        if sum < target {
            left_i += 1;
        } else if sum > target {
            right_i -= 1;
        } else {
            return vec![(left_i + 1) as i32, (right_i + 1) as i32];
        }
    }

    panic!("Should not happen");
}

fn main() {
    let nums = Vec::from([2,7,11,15]);
    let target = 9;

    let nums = Vec::from([-1,0]);
    let target = -1;
    
    let nums = Vec::from([2,7,11,15]);
    let target = 9;
 
    println!("Two numbers that make sum are at: {:?}", two_sum(nums, target));
}
