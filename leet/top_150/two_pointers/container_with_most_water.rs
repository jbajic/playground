/*You are given an integer array height of length n. There are n vertical lines drawn such*/
/*that the two endpoints of the ith line are (i, 0) and (i, height[i]).*/
/*Find two lines that together with the x-axis form a container, such that the container*/
/*contains the most water.*/
/*Return the maximum amount of water a container can store.*/
/*Notice that you may not slant the container.*/

pub fn max_area(height: Vec<i32>) -> i32 {
    let mut left = 0;
    let mut right = height.len() - 1;
    let mut max_water = 0;

    while left < right {
        let min_height = std::cmp::min(height[left], height[right]) as usize;
        max_water = std::cmp::max(max_water, min_height * (right - left)) as usize;
        if height[left] < height[right] {
            left += 1;
        } else {
            right -= 1;
        }
    }

    max_water as i32
}

fn main() {
   println!("Max area covered in water {}", max_area(vec![1,8,6,2,5,4,8,3,7])); 
}
