/*Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. 
* The order of the elements may be changed. Then return the number of elements in nums which are not equal to val.*/
/*Consider the number of elements in nums which are not equal to val be k, to get accepted, you need to do the following things:*/
/*Change the array nums such that the first k elements of nums contain the elements which are not equal to val.
* The remaining elements of nums are not important as well as the size of nums.*/
/*Return k.*/

pub fn remove_element(nums: &mut Vec<i32>, val: i32) -> i32 {
        let mut non_vals = 0;
        let mut size = nums.len();
        let mut i = 0;

        while i < size {
            if nums[i] == val {
                nums.as_mut_slice().copy_within(i+1..size, i);
                size -= 1;
            } else {
                i +=1;
                non_vals += 1;
            }
        }
        return non_vals as i32;
    }

fn main() {
    let mut nums = Vec::from([3,2,2,3]);
    let val = 3;

    let res = remove_element(&mut nums, 2);

    println!("After removing 2 {:?}", nums);
    println!("Res {:?}", res);
}
