/*You are given two integer arrays nums1 and nums2, sorted in non-decreasing order,
* and two integers m and n, representing the number of elements in nums1 and nums2 respectively.*/
/*Merge nums1 and nums2 into a single array sorted in non-decreasing order.*/
/*The final sorted array should not be returned by the function, but instead be stored inside the array nums1.
* To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that
* should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.*/


pub fn merge(nums1: &mut Vec<i32>, m: i32, nums2: &mut Vec<i32>, n: i32) {
    let mut i: usize = 0;
    let mut j: usize = 0;

    while j < nums2.len() && i < (m as usize + j) as usize {
        if nums1[i] < nums2[j] {
            i += 1;
        } else if nums2[j] < nums1[i] {
            nums1.insert(i, nums2[j]);
            i += 1;
            j += 1;
        } else {
            nums1.insert(i, nums2[j]);
            i += 1;
            j += 1;
        }
    }

    while j < nums2.len() {
        nums1[i] = nums2[j];
        i += 1;
        j += 1;
    }
    nums1.drain((n+m)as usize..);
}

fn main() {
    let mut nums1 = Vec::from([1,2,3,0,0,0]);
    let m = 3;
    let mut nums2 = Vec::from([2,5,6]);
    let n = 3;

    merge(&mut nums1, m, &mut nums2, n);
    println!("Merged {:?}", nums1);
}
