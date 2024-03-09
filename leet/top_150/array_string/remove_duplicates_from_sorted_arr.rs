/*Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. */
/*The relative order of the elements should be kept the same.  Then return the number of unique elements in nums.*/
/*Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:*/
/*Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. */
/*The remaining elements of nums are not important as well as the size of nums.*/
/*Return k.*/

pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
    let mut i = 0;
    let mut unique = 0;
    let mut size = nums.len();

    while i < size - 1 {
        if nums[i] == nums [i+1] {
            nums.as_mut_slice().copy_within((i+1)..size, i);
            size -= 1;
        } else {
            unique += 1;
            i += 1;
        }
    }

    return unique+1;
}

fn main() {
    let mut nums = Vec::from([1,1,2]);

    let res = remove_duplicates(&mut nums);
    println!("After removing duplucates: {:?}", nums);
    println!("Res: {}", res);
}
