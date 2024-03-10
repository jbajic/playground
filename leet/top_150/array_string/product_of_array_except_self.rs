/*Given an integer array nums, return an array answer such that answer[i] is equal to the product */
/*of all the elements of nums except nums[i].*/
/*The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.*/
/*You must write an algorithm that runs in O(n) time and without using the division operation.*/
/*Follow up: Can you solve the problem in O(1) extra space complexity? */
/*(The output array does not count as extra space for space complexity analysis.)*/

pub fn product_except_self(nums: Vec<i32>) -> Vec<i32> {
    let mut prefix: Vec<i32> = Vec::new();
    let mut postfix: Vec<i32> = nums.clone();
    for i in 0..nums.len() {
        if i == 0 {
            prefix.push(nums[i]);
        } else {
            prefix.push(nums[i] * prefix[i-1]);
        }
    }

    for i in (0..nums.len()).rev() {
        if i == nums.len() - 1 {
            postfix[i] = nums[i];
        } else {
            postfix[i] = nums[i] * postfix[i+1];
        }
    }

    let mut result = Vec::new();
    for i in 0..nums.len() {
        if i == 0 {
            result.push(1*postfix[i+1]);
        } else if i == nums.len() - 1{
            result.push(1*prefix[i-1]);
        } else {
            result.push(prefix[i-1] * postfix[i+1]);
        }
    }


    result
}


fn main() {
    let nums = Vec::from([1,2,3,4]);
    //let nums = Vec::from([-1,1,0,-3,3]);
    
    println!("Res: {:?}", product_except_self(nums));
}
