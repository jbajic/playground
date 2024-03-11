/*There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.*/
/*You are giving candies to these children subjected to the following requirements:*/
/*Each child must have at least one candy.*/
/*Children with a higher rating get more candies than their neighbors.*/
/*Return the minimum number of candies you need to have to distribute the candies to the children.*/


// O(n^2)
pub fn candy(ratings: Vec<i32>) -> i32 {
    let mut candies = vec![1; ratings.len()];
    let mut candy_set = false;

    if ratings.len() == 1 {
        return 1;
    } else if ratings.len() == 2 {
        if ratings[0] == ratings[1] {
            return 2;
        } else {
            return 3;
        }
    }
    while !candy_set {
        candy_set = true;
        for win in (0..ratings.len()).collect::<Vec<_>>().windows(3) {
            let first = win[0];
            let mid = win[1];
            let third = win[2];
            if ratings[mid] > ratings[first] && candies[mid] <= candies[first] {
                candies[mid] += candies[first] - candies[mid] + 1;
                candy_set = false;
            } else if ratings[mid] < ratings[first] && candies[mid] >= candies[first] {
                candies[first] += candies[mid] - candies[first] + 1;
                candy_set = false;
            }

            if ratings[mid] > ratings[third] && candies[mid] <= candies[third] {
                candies[mid] += candies[third] - candies[mid] + 1;
                candy_set = false;
            } else if ratings[mid] < ratings[third] && candies[mid] >= candies[third] {
                candies[third] += candies[mid] - candies[third] + 1;
                candy_set = false;
            }
        }
    }
 
    candies.iter().sum()
}

// O(2n)
pub fn candy_2(ratings: Vec<i32>) -> i32 {
    let mut candies = vec![1; ratings.len()];
    
    // First left to right checking left neibhour
    for i in 1..ratings.len() {
        if ratings[i] < ratings[i-1] && candies[i] >= candies[i-1] {
            candies[i-1] += candies[i] - candies[i-1] + 1;
        } else if ratings[i] > ratings[i-1] && candies[i] <= candies[i-1] {
            candies[i] += candies[i-1] - candies[i] + 1;
        }
    }
    println!("First: {:?}", candies);

    // Then we iterate in opposite order
    for i in (0..ratings.len()-1).rev() {
        println!("{} and {}", i, i+1);
        if ratings[i] < ratings[i+1] && candies[i] >= candies[i+1] {
            candies[i+1] += candies[i] - candies[i+1] + 1;
        } else if ratings[i] > ratings[i+1] && candies[i] <= candies[i+1] {
            candies[i] += candies[i+1] - candies[i] + 1;
        }
    }

    println!("Second: {:?}", candies);

    candies.iter().sum()
}



fn main() {
    let children = Vec::from([1,3,2,2,1]);
    let children = Vec::from([1,1]);
    let children = Vec::from([1,2]);
    let children = Vec::from([1,3,4,5,2]);

    println!("Min number of candies: {}", candy_2(children));
}
