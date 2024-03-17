/*Given an integer array nums sorted in non-decreasing order, remove some duplicates in-place such that each unique element*/
/*appears at most twice. The relative order of the elements should be kept the same.*/
/*Since it is impossible to change the length of the array in some languages, you must instead have the result be placed*/
/*in the first part of the array nums. More formally, if there are k elements after removing the duplicates, then the first k*/
/*elements of nums should hold the final result. It does not matter what you leave beyond the first k elements.*/
/*Return k after placing the final result in the first k slots of nums.*/
/*Do not allocate extra space for another array. You must do this by modifying the input array in-place with O(1) extra memory.*/


pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
    let mut i = 0;
    let mut size = nums.len();
    let mut k = 0;

    if size > 2 {
        while i < size - 2 {
            if nums[i] == nums[i+1] && nums[i] == nums[i+2] {
                nums.as_mut_slice().copy_within(i+3..size, i+2);
                size -= 1;
            } else {
                i += 1;
                k += 1;
            }
        }
    }

    size as i32
}

pub fn remove_duplicates_2(nums: &mut Vec<i32>) -> i32 {
    let mut i = 0;
    let mut j = 1;
    let mut same = false;

    while j < nums.len() {
        if nums[i] == nums[j] && same {
            j += 1;
        } else if nums[i] == nums[j] {
            same = true;
            nums[i+1] = nums[j];
            i += 1;
            j += 1;
        } else {
            same = false;
            nums[i+1] = nums[j];
            i += 1;
            j += 1;
        }
    }

    return (i + 1) as i32;
}

fn main() {
    let mut nums = Vec::from([1,1,1,2,2,3]);
    let mut nums = Vec::from([0,0,1,1,1,1,2,3,3]);
    let k = remove_duplicates_2(&mut nums);

    println!("After removing {:?}", nums);
    println!("Res: {}", k);
}
