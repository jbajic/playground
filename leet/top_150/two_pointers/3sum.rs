/*Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]*/
/*such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.*/
/*Notice that the solution set must not contain duplicate triplets.*/

use std::collections::HashSet;

// Stupid solution
pub fn three_sum(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut triplets: HashSet<(i32, i32, i32)> = HashSet::new();
    
    for i in 0..(nums.len() - 2) {
        for j in (i+1)..(nums.len() - 1) {
            for k in (j+1)..nums.len() {
                if nums[i] + nums[j] + nums[k] == 0 {
                    let mut sorted = [nums[i], nums[j], nums[k]];
                    sorted.sort();
                    triplets.insert((sorted[0], sorted[1], sorted[2]));
                }
             }
        }
    }

    triplets.into_iter()
        .map(|(f,s,t)| Vec::from([f,s,t]))
        .collect()
}

// Sort + TwoSum sorted solution
pub fn three_sum_2(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut triplets: Vec<Vec<i32>> = Vec::new();
    nums.sort();
    let mut seen: HashSet<(i32, i32, i32)> = HashSet::new();
    
    for i in 0..(nums.len() - 2) {
        let mut left = i + 1;
        let mut right = nums.len() - 1;

        while left < right {
            let target = nums[i] + nums[left] + nums[right];
            if target < 0 {
                left += 1;
            } else if target > 0 {
                right -= 1;
            } else {
                let t = (nums[i], nums[left], nums[right]);
                if !seen.contains(&t) {
                    seen.insert(t);
                    triplets.push(Vec::from([nums[i], nums[left], nums[right]]));
                }
                right -= 1;
                left += 1;
            }
        }
    }

    triplets
}



fn main() {
    let nums = Vec::from([-1,0,1,2,-1,-4]);

    let nums = Vec::from([-2,0,0,2,2]);

    println!("The triplet that makes up 0: {:?}", three_sum_2(nums));
} 
