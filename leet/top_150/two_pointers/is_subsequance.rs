/*Given two strings s and t, return true if s is a subsequence of t, or false otherwise.*/
/*A subsequence of a string is a new string that is formed from the original string by*/
/*deleting some (can be none) of the characters without disturbing the relative positions*/
/*of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).*/

pub fn is_subsequence(s: String, t: String) -> bool {
    let small: Vec<_> = s.chars().collect();
    let big: Vec<_> = t.chars().collect();
    if small.len() > big.len() {
        return false;
    } else if small.len() == 0 {
        return true;
    }
    let mut big_i = 0;
    let mut small_i = 0;
    while big_i < big.len() {
        if big[big_i] == small[small_i] {
            small_i += 1;
            if small_i == small.len() {
                return true;
            }
        }
        big_i += 1;
    }
   
    return false;
}

fn main() {
    println!("Is subsequance {:?}", is_subsequence("abc".to_string(), "ahbgdc".to_string()));
    println!("Is subsequance {:?}", is_subsequence("aec".to_string(), "ahbgdc".to_string()));
    println!("Is subsequance {:?}", is_subsequence("".to_string(), "ahbgdc".to_string()));
}
