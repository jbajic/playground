/*Given n non-negative integers representing an elevation map where the width*/
/*of each bar is 1, compute how much water it can trap after raining.*/

pub fn trap(height: Vec<i32>) -> i32 {
    let mut current_max = 0;
    let mut max_left = vec![0; height.len()];
    for i in 0..height.len() {
        max_left[i] = current_max;
        current_max = std::cmp::max(height[i], current_max);
    }

    let mut max_right = vec![0; height.len()];
    current_max = 0;
    for i in (0..height.len()).collect::<Vec<_>>().iter().rev() {
        max_right[*i] = current_max;
        current_max = std::cmp::max(height[*i], current_max);
    }

    let mut min_left_right = Vec::new();
     for i in 0..height.len() {
        min_left_right.push(std::cmp::min(max_left[i], max_right[i]));
    }

    let mut trapped = 0;
    for i in 0..height.len() {
        let res = min_left_right[i] - height[i];
        if res > 0 {
            trapped += res;
        }
    }
   
    println!("max right {:?}", max_right);
    println!("max left {:?}", max_left);
    trapped
}

// Also two pointers method can work

fn main() {
    let height = Vec::from([0,1,0,2,1,0,1,3,2,1,2,1]);
    
    println!("Trapped water: {}", trap(height));
}
